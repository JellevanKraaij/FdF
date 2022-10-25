#include "fdf.h"
#include "line.h"
#include <MLX42/MLX42.h>
#include <stdio.h>
#include <math.h>

static int	f_sign(int p0, int p1)
{
	if (p0 < p1)
		return (1);
	return (-1);
}

static int	calc_color(t_point p1, t_point p2, int delta[2], double result[4])
{
	const uint8_t		*p1color = (uint8_t *)&p1.color;
	const uint8_t		*p2color = (uint8_t *)&p2.color;
	int					axis;
	int					i;

	if (delta[X] < delta[Y])
		axis = Y;
	else
		axis = X;
	i = 0;
	while (i < 4)
	{
		result[i] = (double)((int)p2color[i] - (int)p1color[i]) / delta[axis];
		i++;
	}
	return (axis);
}

static void add_color(int *color, double color_add[4], int color_start, int pos)
{
	uint8_t	*_color;
	uint8_t	*_color_start;
	int		i;

	_color = (uint8_t *)color;
	_color_start = (uint8_t *)&color_start;
	i = 0;
	while (i < 4)
	{
		_color[i] = (int)_color_start[i] + (color_add[i] * pos);
		i++;
	}
}

static t_line	init_line(t_point p1, t_point p2)
{
	t_line	line;

	line.p0[X] = p1.cords[X];
	line.p0[Y] = p1.cords[Y];
	line.p1[X] = p2.cords[X];
	line.p1[Y] = p2.cords[Y];
	line.delta[X] = abs(line.p1[X] - line.p0[X]);
	line.sign[X] = f_sign(line.p0[X], line.p1[X]);
	line.delta[Y] = abs(line.p1[Y] - line.p0[Y]);
	line.sign[Y] = f_sign(line.p0[Y], line.p1[Y]);
	line.error[0] = line.delta[X] + -line.delta[Y];
	line.color = p1.color;
	line.color_axis = calc_color(p1, p2, line.delta, line.color_add);
	return (line);
}

void	draw_line(t_point p1, t_point p2, \
		void (*plotf)(int, int, int, void *), void *data)
{
	t_line	line;

	line = init_line(p1, p2);
	while (1)
	{
		add_color(&line.color, line.color_add, p1.color, abs(line.p0[line.color_axis] - (int)p1.cords[line.color_axis]));
		plotf(line.p0[X], line.p0[Y], line.color, data);
		if (line.p0[X] == line.p1[X] && line.p0[Y] == line.p1[Y])
			break ;
		line.error[1] = 2 * line.error[0];
		if (line.error[1] >= -line.delta[Y])
		{
			line.error[0] = line.error[0] - line.delta[Y];
			line.p0[X] = line.p0[X] + line.sign[X];
		}
		if (line.error[1] <= line.delta[X])
		{
			line.error[0] = line.error[0] + line.delta[X];
			line.p0[Y] = line.p0[Y] + line.sign[Y];
		}
	}
}
