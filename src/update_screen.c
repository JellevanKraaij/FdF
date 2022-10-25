/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_screen.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:59:13 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:59:13 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <MLX42/MLX42.h>
#include <math.h>

void	clear_img(mlx_image_t *img)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, 0XFF000000);
			j++;
		}
		i++;
	}
}

static void	translate_map(t_map *map, t_fdf *data)
{
	double	vector[3];
	double	x;
	double	y;

	if ((int)data->projection == ISO)
	{
		x = ((data->x_offset / cos(0.523598776)) + \
			(data->y_offset / sin(0.523598776)));
		y = (-(data->x_offset / cos(0.523598776)) + \
			(data->y_offset / sin(0.523598776)));
	}
	else
	{
		x = data->x_offset;
		y = data->y_offset;
	}
	x *= (1 + data->map_scale / data->map_scale) - 1;
	y *= (1 + data->map_scale / data->map_scale) - 1;
	vector[X] = x - (((double)data->map->column_count - 1.0) / 2.0);
	vector[Y] = y - (((double)data->map->row_count - 1.0) / 2.0);
	vector[Z] = 0;
	map_apply_offset(map, vector);
}

static void	scale_map(t_map *map, t_fdf *data)
{
	double	vector[3];

	if (data->scale < 0)
		data->scale = 0;
	vector[X] = data->scale;
	vector[Y] = data->scale;
	vector[Z] = data->scale * data->z_scale;
	map_apply_scale(map, vector);
}

static void	center_map(t_map *map, t_fdf *data)
{
	double	vector[3];

	vector[X] = (data->img[0]->width / 2);
	vector[Y] = (data->img[0]->height / 2);
	vector[Z] = 0;
	map_apply_offset(map, vector);
}

void	update_screen(t_fdf *data)
{
	t_map	*map;

	map = dup_map(data->map);
	translate_map(map, data);
	scale_map(map, data);
	if (data->projection == ISO)
		map_project_iso(map);
	center_map(map, data);
	if (map->column_count == 1 && map->row_count == 1)
		plot_point(data->img[!data->current_img], map);
	else
		plot_lines(data->img[!data->current_img], map);
	mlx_set_instance_depth(data->img[!data->current_img]->instances, 0);
	mlx_set_instance_depth(data->img[data->current_img]->instances, 1);
	clear_img(data->img[data->current_img]);
	data->current_img = !data->current_img;
	destroy_map(map);
}
