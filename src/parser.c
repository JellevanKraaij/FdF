/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:59:01 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:59:01 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <get_next_line.h>

static	void	add_point(t_point **points, t_point point)
{
	static t_point	*last;
	static size_t	used_len;
	static size_t	buffersize = 1;
	static size_t	len;

	if (*points == NULL)
	{
		used_len = 0;
		len = 0;
		*points = null_exit(ft_calloc(buffersize, sizeof(t_point)));
		last = *points;
	}
	if (used_len >= buffersize)
	{
		buffersize = len;
		*points = ft_reallocf(*points, len * sizeof(t_point), \
			(len + buffersize) * sizeof(t_point));
		used_len = 0;
		last = &(*points)[len];
	}
	*last = point;
	last++;
	used_len++;
	len++;
}

static	char	**get_file_row(int fd)
{
	char	*line;
	char	**split_line;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	split_line = null_exit(ft_splitset(line, " \n"));
	free(line);
	return (split_line);
}

static	int	parse_num_color(char *cell, int *height, int *color)
{
	char	*loc;
	char	*num;
	int		ret;
	int		color_len;
	int		height_len;

	ret = 0;
	loc = ft_strchr(cell, ',');
	*color = 0xFFFFFF;
	if (loc == NULL)
		return (ft_atoi_safe(cell, height));
	num = null_exit(ft_strndup(cell, (size_t)loc - (size_t)cell));
	height_len = ft_atoi_safe(num, height);
	color_len = ft_atoi_safe((loc + 1), color);
	if (height_len < 0 || color_len < 0)
		ret = -1;
	if (color_len <= 6)
	{
		*color = *color << 8;
		*color |= 0xFF;
	}
	free(num);
	return (ret);
}

int	parse_line(int fd, t_map *map)
{
	char	**row;
	size_t	i;
	int		num;
	int		color;

	row = get_file_row(fd);
	if (row == NULL)
		return (1);
	if (row[0] == NULL)
		print_error_exit("fdf: empty line", EXIT_FAILURE);
	i = 0;
	while (row[i])
	{
		if (map->column_count != 0 && i >= map->column_count)
			print_error_exit("fdf: row is too long", EXIT_FAILURE);
		if (parse_num_color(row[i], &num, &color) < 0)
			print_error_exit("fdf: invalid number", EXIT_FAILURE);
		add_point(&map->points, (t_point){.cords = \
			{i, map->row_count, num}, .color = color});
		i++;
	}
	ft_split_free(row);
	map->column_count = i;
	return (0);
}

t_map	*parse_map(char *filename)
{
	int		fd;
	t_map	*map;

	map = init_map();
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("fdf");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (parse_line(fd, map))
			break ;
		map->row_count++;
	}
	return (map);
}
