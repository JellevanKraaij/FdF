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

typedef struct s_lookup_key
{
	enum keys key;
	double	  amount;
	double	  *result;
}	t_lookup_key;

void handle_keys(t_data *data)
{
	const t_lookup_key key_lookup[] =
	{
		{MLX_KEY_D, data->x_offset + 5, &data->x_offset},
		{MLX_KEY_A, data->x_offset - 5, &data->x_offset},
		{MLX_KEY_S, data->y_offset + 5, &data->y_offset},
		{MLX_KEY_W, data->y_offset - 5, &data->y_offset},
		{MLX_KEY_F, data->scale * 0.95, &data->scale},
		{MLX_KEY_R, data->scale * 1.05, &data->scale},
		{MLX_KEY_T, data->z_scale + 0.05, &data->z_scale},
		{MLX_KEY_G, data->z_scale - 0.05, &data->z_scale},
	};
	const size_t	lookup_size = sizeof(key_lookup) / sizeof (t_lookup_key);
	size_t			i;
	t_lookup_key	current;

	i = 0;
	while (i < lookup_size)
	{

		current = key_lookup[i];
		if (mlx_is_key_down(data->mlx, current.key))
		{
			data->update = 1;
			*current.result = current.amount;
		}
		i++;
	}
}

void	key_hook(mlx_key_data_t keydata, void *data_p)
{
	t_data *data;

	data = data_p;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		data->update = 1;
		data->projection = !data->projection;
	}
}

void	resize_hook(int32_t width, int32_t height, void *data_p)
{
	t_data *data;

	data = data_p;
	data->update = 1;
	mlx_resize_image(data->img, width, height);
}

void	loop_hook(void *data_p)
{
	t_data *data;

	data = data_p;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		return ;
	}
	handle_keys(data);
	if (data->update)
	{
		update_screen(data);

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
	data.map_scale = ft_smallest((float)WIDTH / 2 / data.map->column_count, (float)HEIGHT / 2 / data.map->row_count);
	data.scale = data.map_scale;
	printf("map scale = %f\n", data.map_scale);
	data.z_scale = 1;
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_resize_hook(data.mlx, resize_hook, &data);
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	destroy_map(data.map);
	return (EXIT_SUCCESS);
}
