/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scaling.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:59:06 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:59:06 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	point_apply_scale(t_point *point, double scale[3])
{
	point->cords[X] *= scale[X];
	point->cords[Y] *= scale[Y];
	point->cords[Z] *= scale[Z];
}

void	map_apply_scale(t_map *map, double scale[3])
{
	size_t	i;

	i = 0;
	while (i < (map->column_count * map->row_count))
	{
		point_apply_scale(&map->points[i], scale);
		i++;
	}
}
