/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_image.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:58:50 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:58:50 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "line.h"

static int	possible_on_screen(t_point point1, t_point point2, mlx_image_t *img)
{
	const double	p0[2] = {point1.cords[X], point1.cords[Y]};
	const double	p1[2] = {point2.cords[X], point2.cords[Y]};

	if ((p0[X] < 0 && p1[X] < 0) || (p0[Y] < 0 && p1[Y] < 0))
		return (0);
	if (p0[X] >= img->width && p1[X] >= img->width)
		return (0);
	if (p0[Y] >= img->height && p1[Y] >= img->height)
		return (0);
	return (1);
}

static void	draw_point(int x, int y, int color, void *data)
{
	mlx_image_t	*img;

	img = data;
	if (x >= 0 && (uint32_t)x < img->width \
		&& y >= 0 && (uint32_t)y < img->height)
		mlx_put_pixel(img, x, y, color);
	(void)color;
}

void	plot_lines(mlx_image_t *img, t_map *map)
{
	size_t	i;
	t_point	point1;
	t_point	point2;

	i = 0;
	while (i < map->row_count * map->column_count)
	{
		point1 = map->points[i];
		if ((i % map->column_count) + 1 < map->column_count)
		{
			point2 = map->points[i + 1];
			if (possible_on_screen(point1, point2, img))
				draw_line(point1, point2, draw_point, img);
		}
		if ((i / map->column_count) + 1 < map->row_count)
		{
			point2 = map->points[i + map->column_count];
			if (possible_on_screen(point1, point2, img))
				draw_line(point1, point2, draw_point, img);
		}
		i++;
	}
}

void	plot_point(mlx_image_t *img, t_map *map)
{
	draw_point(map->points[0].cords[X], map->points[0].cords[Y], \
	map->points[0].color, img);
}
