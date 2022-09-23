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

void	print_3dmap(t_map *map)
{
	t_list		*tmp;
	size_t		i;

	tmp = map->elements;
	i = 1;
	while (tmp)
	{
		printf("%d,0x%06X", ((t_3dpoint *)tmp->content)->height, ((t_3dpoint *)tmp->content)->color);
		if (i % map->column_count)
			printf(" ");
		else
			printf("\n");
		i++;
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv)
{
	t_map	*map_3d;

	if (argc < 2)
	{
		ft_putendl_fd("fdf: missing parameter", STDERR_FILENO);
		ft_putendl_fd("usage: ./fdf [file]", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	map_3d = parse_map(argv[1]);
	printf("map rowlen = %lu\n", map_3d->column_count);
	print_3dmap(map_3d);
	destroy_map(map_3d);
	return (EXIT_SUCCESS);
}
