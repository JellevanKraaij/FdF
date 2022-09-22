#include <fdf.h>
#include <libft.h>

t_2dmap	*init_2dmap(void)
{
	return (null_exit(ft_calloc(1, sizeof(t_2dmap))));
}

t_2dmap	*create_2dmap(t_list *elements, int row_len)
{
	t_2dmap	*ret;

	ret = init_2dmap();
	ret->elements = elements;
	ret->row_len = row_len;
	return (ret);
}
