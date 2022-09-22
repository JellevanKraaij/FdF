/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 17:00:21 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/03/24 17:00:21 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

void	print_2dmap(t_2dmap *map)
{
	t_list		*tmp;
	size_t		i;

	tmp = map->elements;
	i = 1;
	while (tmp)
	{
		printf("%d", ((t_mappoint *)tmp->content)->height);
		if (i % map->row_len)
			printf(",");
		else
			printf("\n");
		i++;
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv)
{
	t_2dmap	*map;

	if (argc < 2)
	{
		ft_putendl_fd("fdf: missing parameter", STDERR_FILENO);
		ft_putendl_fd("usage: ./fdf [file]", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	map = parse_map(argv[1]);
	printf("map rowlen = %lu\n", map->row_len);
	print_2dmap(map);
	return (EXIT_SUCCESS);
}
