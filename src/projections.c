#include "fdf.h"
#include <math.h>

void	point_apply_iso(t_point *point)
{
	double x;
	double y;

	x = (point->cords[X] - point->cords[Y]) * cos(0.523598776);
	y = point->cords[Y] + (point->cords[X] - (point->cords[Z] * 0.5)) * sin(0.523598776);

	point->cords[X] = x;
	point->cords[Y] = y;
	point->cords[Z] = 0;
}

void	map_project_iso(t_map *map)
{
	size_t	i;

	i = 0;
	while(i < (map->column_count * map->row_count))
	{
		point_apply_iso(&map->points[i]);
		i++;
	}
}
