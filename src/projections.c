/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   projections.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:59:03 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:59:03 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	point_apply_iso(t_point *point)
{
	double	x;
	double	y;

	x = (point->cords[X] - point->cords[Y]) * cos(0.523598776);
	y = (-point->cords[Z] + point->cords[Y] + point->cords[X]) \
		* sin(0.523598776);
	point->cords[X] = x;
	point->cords[Y] = y;
	point->cords[Z] = 0;
}

void	map_project_iso(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < (map->column_count * map->row_count))
	{
		point_apply_iso(&map->points[i]);
		i++;
	}
}
