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

t_map	*dup_map(t_map *map)
{
	t_map	*ret;
	size_t	point_size;

	ret = null_exit(malloc(sizeof(t_map)));
	ft_memcpy(ret, map, sizeof(t_map));
	point_size = map->column_count * map->row_count * sizeof(t_point);
	ret->points = null_exit(malloc(point_size));
	ft_memcpy(ret->points, map->points, point_size);
	return (ret);
}
