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
#include <MLX42/MLX42.h>
#define WIDTH 1500
#define HEIGHT 1000

void	print_3dmap(t_map *map)
{
	size_t		i;

	i = 0;
	while (i < map->column_count * map->row_count)
	{
		printf("%.0f,0x%06X", map->points[i].cords[Z], map->points[i].color);
		if ((i + 1) % map->column_count)
			printf(" ");
		else
			printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (argc < 2)
	{
		ft_putendl_fd("fdf: missing parameter", STDERR_FILENO);
		ft_putendl_fd("usage: ./fdf [file]", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	map = parse_map(argv[1]);
	printf("map rowlen = %lu\n", map->column_count);
	print_3dmap(map);
	// update_map_screen(map);
	map_to_img(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
	destroy_map(map);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
