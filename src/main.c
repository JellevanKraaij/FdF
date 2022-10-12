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

void	loop_hook(void *data_p)
{
	t_data *data;
	t_map *map;

	data = data_p;
	if (mlx_is_key_down(data->mlx, MLX_KEY_T))
	{
		data->scale[Z]++;
		printf("double %lf\n", data->scale[Z]);
		data->update = 1;
		printf("T\n");
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_G))
	{
		data->scale[Z]--;
		data->update = 1;
		printf("G\n");
	}
	if (data->update)
	{
		printf("update map\n");
		map = copy_map(data->map);
		map_apply_scale(map, data->scale);
		map_project_iso(map);
		double offset[3] = {500, 500, 0};
		map_apply_offset(map, offset);
		map_to_img(data->img, map);
		destroy_map(map);
		data->update = 0;
		printf("update map done\n");
	}
}

int	main(int argc, char **argv)
{
	t_data		data;

	ft_bzero(&data, sizeof(data));
	if (argc < 2)
	{
		ft_putendl_fd("fdf: missing parameter", STDERR_FILENO);
		ft_putendl_fd("usage: ./fdf [file]", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	data.map = parse_map(argv[1]);
	data.update = 1;
	data.scale[X] = 20;
	data.scale[Y] = 20;
	data.scale[Z] = 5;
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
