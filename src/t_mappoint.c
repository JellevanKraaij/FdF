#include <fdf.h>
#include <libft.h>

t_mappoint	*init_mappoint(void)
{
	return (null_exit(ft_calloc(1, sizeof(t_mappoint))));
}

t_mappoint	*create_mappoint(int heigt, int color)
{
	t_mappoint	*ret;

	ret = init_mappoint();
	ret->height = heigt;
	ret->color = color;
	return (ret);
}

void	destroy_mappoint(void *mappoint)
{
	free(mappoint);
}
