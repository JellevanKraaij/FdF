/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:58:55 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:58:55 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <MLX42/MLX42.h>

typedef struct s_lookup_key
{
	enum keys	key;
	double		amount;
	double		*result;
}	t_lookup_key;

void	handle_keys(t_fdf *data)
{
	const t_lookup_key	key_lookup[] = \
	{
	{MLX_KEY_D, data->x_offset + (5 / data->scale), &data->x_offset},
	{MLX_KEY_A, data->x_offset - (5 / data->scale), &data->x_offset},
	{MLX_KEY_S, data->y_offset + (5 / data->scale), &data->y_offset},
	{MLX_KEY_W, data->y_offset - (5 / data->scale), &data->y_offset},
	{MLX_KEY_F, data->scale * 0.95, &data->scale},
	{MLX_KEY_R, data->scale * 1.05, &data->scale},
	{MLX_KEY_T, data->z_scale + 0.05, &data->z_scale},
	{MLX_KEY_G, data->z_scale - 0.05, &data->z_scale},
	};
	size_t				i;
	t_lookup_key		current;

	i = 0;
	while (i < sizeof(key_lookup) / sizeof (t_lookup_key))
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
	t_fdf	*data;

	data = data_p;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		data->update = 1;
		data->projection = !data->projection;
	}
}

void	resize_hook(int32_t width, int32_t height, void *data_p)
{
	t_fdf	*data;

	data = data_p;
	data->update = 1;
	exit_if_true(!mlx_resize_image(data->img[0], width, height));
	exit_if_true(!mlx_resize_image(data->img[1], width, height));
}

void	loop_hook(void *data_p)
{
	t_fdf	*data;

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
