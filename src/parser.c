#include "fdf.h"
#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <get_next_line.h>

size_t	parse_line(int fd, t_list **list)
{
	char	*line;
	char	**split;
	size_t	i;
	int		num;
	t_list	*last;

	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	split = ft_splitset(line, " \n");
	free(line);
	if (split == NULL)
		perror_exit("fdf", EXIT_FAILURE);
	if (split[0] == NULL)
	{
		ft_putendl_fd("fdf: empty line", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = 0;
	last = ft_lstlast(*list);
	while (split[i])
	{
		if (ft_atoi_p(split[i], &num) < 0)
		{
			ft_putendl_fd("fdf: invalid number", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		if (last == NULL)
		{
			*list = null_exit(ft_lstnew(create_mappoint(num, -1)));
			last = *list;
		}
		else
		{
			last->next = null_exit(ft_lstnew(create_mappoint(num, -1)));
			last = last->next;
		}
		i++;
	}
	ft_split_free(split);
	return (i);
}

t_2dmap	*parse_map(char *filename)
{
	int		fd;
	t_2dmap	*map;
	size_t	tmp;

	map = init_2dmap();
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("fdf");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		tmp = parse_line(fd, &map->elements);
		if (tmp == 0)
			break ;
		if (tmp != map->row_len && map->row_len != 0)
		{
			ft_putendl_fd("fdf: row is too long", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		map->row_len = tmp;
	}
	return (map);
}
