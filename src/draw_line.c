#include "fdf.h"
#include "line.h"
#include <MLX42/MLX42.h>
#include <math.h>

static t_color	init_color(t_point p1, t_point p2, int delta[2])
{
	const uint8_t		*p1color = (uint8_t *)&p1.color;
	const uint8_t		*p2color = (uint8_t *)&p2.color;
	int					i;
	t_color				color;

	if (p1.color == p2.color)
	{
		color.change = 0;
		color.original = p1.color;
		return (color);
	}
	color.change = 1;
	if (delta[X] < delta[Y])
		color.axis = Y;
	else
		color.axis = X;
	i = 0;
	while (i < 4)
	{
		color.increase[i] = (double)((int)p2color[i] - \
			(int)p1color[i]) / delta[color.axis];
		color.current[i] = p1color[i];
		i++;
	}
	return (color);
}

static void	add_color(t_color *color)
{
	int		i;

	if (!color->change)
		return ;
	i = 0;
	while (i < 4)
	{
		color->current[i] += color->increase[i];
		i++;
	}
}

static int	get_color(t_color *color)
{
	int		i;
	int		result;
	uint8_t	*_result;

	if (!color->change)
		return (color->original);
	i = 0;
	_result = (uint8_t *)&result;
	while (i < 4)
	{
		_result[i] = color->current[i];
		i++;
	}
	return (result);
}

static t_line	init_line(t_point p1, t_point p2)
{
	t_line	line;

	line.start[X] = p1.cords[X];
	line.start[Y] = p1.cords[Y];
	line.end[X] = p2.cords[X];
	line.end[Y] = p2.cords[Y];
	line.delta[X] = abs(line.end[X] - line.start[X]);
	line.sign[X] = 1;
	if (line.start[X] > line.end[X])
		line.sign[X] = -1;
	line.delta[Y] = abs(line.end[Y] - line.start[Y]);
	line.sign[Y] = 1;
	if (line.start[Y] > line.end[Y])
		line.sign[Y] = -1;
	line.error[0] = line.delta[X] + -line.delta[Y];
	line.color = init_color(p1, p2, line.delta);
	return (line);
}

void	draw_line(t_point p1, t_point p2, \
		void (*plotf)(int, int, int, void *), void *data)
{
	t_line	line;

	line = init_line(p1, p2);
	while (1)
	{
		plotf(line.start[X], line.start[Y], get_color(&line.color), data);
		if (line.start[X] == line.end[X] && line.start[Y] == line.end[Y])
			break ;
		line.error[1] = 2 * line.error[0];
		if (line.error[1] >= -line.delta[Y])
		{
			if (line.color.axis == X)
				add_color(&line.color);
			line.error[0] = line.error[0] - line.delta[Y];
			line.start[X] = line.start[X] + line.sign[X];
		}
		if (line.error[1] <= line.delta[X])
		{
			if (line.color.axis == Y)
				add_color(&line.color);
			line.error[0] = line.error[0] + line.delta[X];
			line.start[Y] = line.start[Y] + line.sign[Y];
		}
	}
}
