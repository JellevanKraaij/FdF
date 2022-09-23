#include <fdf.h>
#include <libft.h>

t_3dpoint	*init_3dpoint(void)
{
	return (null_exit(ft_calloc(1, sizeof(t_3dpoint))));
}

t_3dpoint	*create_3dpoint(int heigt, int color)
{
	t_3dpoint	*ret;

	ret = init_3dpoint();
	ret->height = heigt;
	ret->color = color;
	return (ret);
}

void	destroy_3dpoint(void *mappoint)
{
	free(mappoint);
}
