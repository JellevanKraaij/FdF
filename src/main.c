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

void clear_img(mlx_image_t *img)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, 0);
			j++;
		}
		i++;
	}
}

void	loop_hook(void *data_p)
{
	t_data *data;
	t_map *map;

	data = data_p;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_T))
	{
		data->z_scale += 0.05;
		data->update = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_G))
	{
		data->z_scale -= 0.05;
		data->update = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
	{
		data->scale *= 1.05;
		data->update = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_F))
	{
		data->scale *= 0.95;
		data->update = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->x_offset += 10;
		data->update = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->x_offset -= 10;
		data->update = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->y_offset += 20;
		data->update = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->y_offset -= 20;
		data->update = 1;
	}
	if (data->update)
	{
		map = copy_map(data->map);
		double vector[3];

		double x;
		double y;
		if (data->projection == ISO)
		{
			x = (data->x_offset / 2) + (data->y_offset / 3);
			y = -(data->x_offset / 2) + (data->y_offset / 3);
		}
		else
		{
			x = data->x_offset;
			y = data->y_offset;
		}
		// x /= (data->map_scale * 1.3);
		// y /= (data->map_scale * 1.3);
		x /= (data->map_scale);
		y /= (data->map_scale);
		vector[X] = x - (((double)data->map->column_count - 1.0) / 2.0);
		vector[Y] = y - (((double)data->map->row_count - 1.0) / 2.0);
		vector[Z] = 0;
		map_apply_offset(map, vector);
		vector[X] = data->scale;
		vector[Y] = data->scale;
		vector[Z] = data->scale * data->z_scale;
		map_apply_scale(map, vector);
		map_project_iso(map);
		vector[X] = (WIDTH / 2);
		vector[Y] = (HEIGHT / 2);;
		vector[Z] = 0;
		map_apply_offset(map, vector);
		clear_img(data->img);
		map_to_img(data->img, map);
		destroy_map(map);
		data->update = 0;
	}
}

double ft_smallest(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
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
	data.map_scale = ft_smallest(WIDTH / data.map->column_count / 2, HEIGHT / data.map->row_count / 2);
	data.scale = data.map_scale;
	data.z_scale = 1;
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	destroy_map(data.map);
	return (EXIT_SUCCESS);
}
