#include <fdf.h>
#include <libft.h>

t_2dmap	*init_2dmap(void)
{
	return (null_exit(ft_calloc(1, sizeof(t_2dmap))));
}

void	destroy_2dmap(t_2dmap *map)
{
	ft_lstclear(&map->elements, destroy_mappoint);
	free(map);
}
