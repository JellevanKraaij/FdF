/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   offset.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:58:59 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:58:59 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	point_apply_offset(t_point *point, double offset[3])
{
	point->cords[X] += offset[X];
	point->cords[Y] += offset[Y];
	point->cords[Z] += offset[Z];
}

void	map_apply_offset(t_map *map, double offset[3])
{
	size_t	i;

	i = 0;
	while (i < (map->column_count * map->row_count))
	{
		point_apply_offset(&map->points[i], offset);
		i++;
	}
}
