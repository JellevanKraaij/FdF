#include "fdf.h"
#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <get_next_line.h>

static	void	ft_lstadd_back_quick(t_list **lst, t_list *new)
{
	static t_list	*last = NULL;

	if (new == NULL)
	{
		last = ft_lstlast(*lst);
		return ;
	}
	if (last == NULL)
	{
		last = new;
		*lst = last;
		return ;
	}
	last->next = new;
	last = last->next;
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

	ret = 0;
	loc = ft_strchr(cell, ',');
	*color = 0xFFFFFF;
	if (loc == NULL)
		return (ft_atoi_safe(cell, height));
	num = null_exit(ft_strndup(cell, (size_t)loc - (size_t)cell));
	if (ft_atoi_safe(num, height) < 0 || ft_atoi_safe((loc + 1), color))
		ret = -1;
	free(num);
	return (ret);
}

size_t	parse_line(int fd, t_list **map)
{
	char	**row;
	size_t	i;
	int		num;
	int		color;

	row = get_file_row(fd);
	if (row == NULL)
		return (0);
	if (row[0] == NULL)
		print_error_exit("fdf: empty line", EXIT_FAILURE);
	i = 0;
	while (row[i])
	{
		if (parse_num_color(row[i], &num, &color) < 0)
			print_error_exit("fdf: invalid number", EXIT_FAILURE);
		ft_lstadd_back_quick(map, null_exit(ft_lstnew(\
			create_3dpoint(num, color))));
		i++;
	}
	ft_split_free(row);
	return (i);
}

t_map	*parse_map(char *filename)
{
	int		fd;
	t_map	*map;
	size_t	tmp;

	map = init_map();
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("fdf");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back_quick(&map->elements, NULL);
	while (1)
	{
		tmp = parse_line(fd, &map->elements);
		if (tmp == 0)
			break ;
		if (tmp != map->column_count && map->column_count != 0)
			print_error_exit("fdf: row is too long", EXIT_FAILURE);
		map->column_count = tmp;
		map->row_count++;
	}
	return (map);
}
