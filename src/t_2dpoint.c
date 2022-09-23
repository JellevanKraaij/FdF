#include <fdf.h>
#include <libft.h>

t_2dpoint	*init_2dpoint(void)
{
	return (null_exit(ft_calloc(1, sizeof(t_2dpoint))));
}

t_2dpoint	*create_2dpoint(int color, int x, int y)
{
	t_2dpoint	*ret;

	ret = init_2dpoint();
	ret->color = color;
	ret->x = x;
	ret->y = y;
	return (ret);
}

void	destroy_2dpoint(void *mappoint)
{
	free(mappoint);
}
