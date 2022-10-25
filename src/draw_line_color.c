#include "fdf.h"
#include "line.h"

t_color	init_color(t_point p1, t_point p2, int delta[2])
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

void	add_color(t_color *color)
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

int	get_color(t_color *color)
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
