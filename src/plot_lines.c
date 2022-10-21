#include "fdf.h"
#include <MLX42/MLX42.h>
#include <stdio.h>
#include <math.h>

void	plot(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && (uint32_t)x < img->width && y >= 0 && (uint32_t)y < img->height)
		mlx_put_pixel(img, x, y, color);
}

void plotLine(mlx_image_t *img, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
	int e2;

    while(true)
	{
        plot(img, x0, y0, 0xFFFFFF);
        if (x0 == x1 && y0 == y1)
			break ;
        e2 = 2 * error;
        if (e2 >= dy)
		{
            if (x0 == x1)
				break ;
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx)
		{
            if (y0 == y1)
				break;
            error = error + dx;
            y0 = y0 + sy;
		}
	}
}

int possible_on_screen(int x0, int y0, int x1, int y1, mlx_image_t *img)
{
	if ((x0 < 0 && x1 < 0) || (y0 < 0 && y1 < 0))
		return (0);
	if ((x0 >= (int)img->width && x1 >= (int)img->width) || (y0 >= (int)img->height && y1 >= (int)img->height))
		return (0);
	return (1);
}

void	plot_lines(mlx_image_t *img, t_map *map)
{
	size_t	i;
	int		x0;
	int		y0;
	int		x1;
	int		y1;

	i = 0;
	while(i < map->row_count * map->column_count)
	{
		if ((i % map->column_count) + 1 < map->column_count)
		{
			x0 = map->points[i].cords[X];
			y0 = map->points[i].cords[Y];
			x1 = map->points[i + 1].cords[X];
			y1 = map->points[i + 1].cords[Y];
			if (possible_on_screen(x0, y0, x1, y1, img))
				plotLine(img, x0, y0, x1, y1);
		}
		if ((i / map->column_count) + 1 < map->row_count)
		{
			x0 = map->points[i].cords[X];
			y0 = map->points[i].cords[Y];
			x1 = map->points[i + map->column_count].cords[X];
			y1 = map->points[i + map->column_count].cords[Y];
			if (possible_on_screen(x0, y0, x1, y1, img))
				plotLine(img, x0, y0, x1, y1);
		}
		i++;
	}
}
