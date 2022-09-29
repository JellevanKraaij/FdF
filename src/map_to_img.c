// #include "fdf.h"
// #include <MLX42/MLX42.h>
// #include <stdio.h>

// void	plot(mlx_image_t *img, int x, int y, int color)
// {
// 	if (x >= 0 && (uint32_t)x < img->width && y >= 0 && (uint32_t)y < img->height)
// 		mlx_put_pixel(img, x, y, color);
// }

// void plotLine(mlx_image_t *img, int x0, int y0, int x1, int y1)
// {
//     int dx = abs(x1 - x0);
//     int sx = x0 < x1 ? 1 : -1;
//     int dy = -abs(y1 - y0);
//     int sy = y0 < y1 ? 1 : -1;
//     int error = dx + dy;
// 	int e2;
    
//     while(true)
// 	{
//         plot(img, x0, y0, 0xFFFFFF);
//         if (x0 == x1 && y0 == y1)
// 			break ;
//         e2 = 2 * error;
//         if (e2 >= dy)
// 		{
//             if (x0 == x1)
// 				break ;
//             error = error + dy;
//             x0 = x0 + sx;
//         }
//         if (e2 <= dx)
// 		{
//             if (y0 == y1)
// 				break;
//             error = error + dx;
//             y0 = y0 + sy;
// 		}
// 	}
// }

// void	map_to_img(mlx_image_t *img, t_map *map)
// {
// 	size_t i;
// 	size_t j;
// 	t_2dpoint point1;
// 	t_2dpoint point2;

// 	i = 0;
// 	while (i < map->row_count)
// 	{
// 		j = 0;
// 		while (j < map->column_count)
// 		{
// 			point1 = map->map_2d[i][j];
// 			if (j + 1 < map->column_count)
// 			{
// 				point2 = map->map_2d[i][j + 1];
// 				printf("line\n");
// 				plotLine(img, point1.x, point1.y, point2.x, point2.y);
// 			}
// 			if (i + 1 < map->row_count)
// 			{
// 				printf("line\n");
// 				point2 = map->map_2d[i + 1][j];
// 				plotLine(img, point1.x, point1.y, point2.x, point2.y);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }