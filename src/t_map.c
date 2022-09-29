#include <fdf.h>
#include <libft.h>

t_map	*init_map(void)
{
	return (null_exit(ft_calloc(1, sizeof(t_map))));
}

void	destroy_map(t_map *map)
{
	free(map->points);
	free(map);
}