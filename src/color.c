/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 18:02:48 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/12/18 18:02:48 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_percent(unsigned int n1, unsigned int n2, unsigned int current)
{
	double	p;
	double	d;

	p = current - n1;
	d = n2 - n1;
	if (d == 0)
		return (1.0);
	return (p / d);
}

void	point_apply_color(t_point *point, \
	unsigned int z_min, unsigned int z_max)
{
	double	pct;

	pct = get_percent(z_min, z_max, point->cords[Z]);
	if (pct < 0.15)
		point->color = 0x00202eff;
	else if (pct < 0.2)
		point->color = 0x003f5cff;
	else if (pct < 0.3)
		point->color = 0x2c4875ff;
	else if (pct < 0.4)
		point->color = 0x8a508fff;
	else if (pct < 0.5)
		point->color = 0xbc5090ff;
	else if (pct < 0.6)
		point->color = 0xff6361ff;
	else if (pct < 0.7)
		point->color = 0xff8531ff;
	else if (pct < 0.8)
		point->color = 0xffa600ff;
	else
		point->color = 0xffd380ff;
}

void	map_apply_color(t_map *map)
{
	size_t			i;
	unsigned int	z_max;
	unsigned int	z_min;

	i = 0;
	z_max = 0;
	z_min = UINT_MAX;
	while (i < (map->column_count * map->row_count))
	{
		if (map->points[i].cords[Z] < z_min)
			z_min = map->points[i].cords[Z];
		if (map->points[i].cords[Z] > z_max)
			z_max = map->points[i].cords[Z];
		i++;
	}
	i = 0;
	while (i < (map->column_count * map->row_count))
	{
		point_apply_color(&map->points[i], z_min, z_max);
		i++;
	}
}
