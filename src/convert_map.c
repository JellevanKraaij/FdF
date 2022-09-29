// #include "fdf.h"
// #include <libft.h>
// #include <math.h>

// double to_degrees(double radians) {
//     return radians * (180.0 / M_PI);
// }

// t_2dpoint	calc_screen_xy(double x, double y, double z, int color)
// {
// 	t_2dpoint	ret;
// 	// const double THETA = 0.3;
// 	// const double PHI = 1.3;
// 	// const double RHO = 10000;
// 	// const double D = 100000;
// 	// const double S1 = sin(THETA);
// 	// const double S2 = sin(PHI);
// 	// const double C1 = cos(THETA);
// 	// const double C2 = cos(PHI);

// 	// const double XE = -1 * x * S1 + y * C1;
// 	// const double YE = -1 * x * C1 * C2 - y * S1 * C2 + z * S2;
// 	// const double ZE = -1 * x * C1 * S2 - y * S1 * S2 - z * C2 + RHO;

// 	// ret.color = color;
// 	// ret.x = (D * XE / ZE) + 500;
// 	// ret.y = (D * YE / ZE) + 500;

// 	// ret.color = color;
// 	// ret.x = (((x - z) / sqrt(9)) * 20) + 500;
// 	// ret.y = (((x + 2 * y + z) / sqrt(9)) * 20) + 500;

// 	int rot	= 90;
// 	ret.color = color;
// 	ret.x = (x * cos(to_degrees(rot))) + (y * cos(to_degrees(rot + 120))) + (z * cos(to_degrees(rot - 120)));
// 	ret.y = (x * sin(to_degrees(rot))) + (y * sin(to_degrees(rot + 120))) + (z * sin(to_degrees(rot - 120)));
// 	ret.x = (ret.x * 20) + 200;
// 	ret.y = (ret.y * 20) + 200;
// 	return (ret);
// }

// void	update_map_screen(t_map *map)
// {
// 	t_3dpoint	*point;
// 	t_list		*tmp;
// 	size_t		i;

// 	i = 0;
// 	tmp = map->map_3d;
// 	map->map_2d = ft_calloc(map->row_count, sizeof(t_2dpoint *));
// 	while (tmp != NULL)
// 	{
// 		point = tmp->content;
// 		if (i % map->column_count == 0)
// 			map->map_2d[i / map->column_count] = ft_calloc(map->column_count, sizeof(t_2dpoint));
// 		map->map_2d[i / map->column_count][i % map->column_count] = calc_screen_xy(i % map->column_count, i / map->column_count, point->height, point->color);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }
