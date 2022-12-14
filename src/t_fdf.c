/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_fdf.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:59:09 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:59:09 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <MLX42/MLX42.h>

double	fdf_smallest(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	init_mlx(int w_width, int w_height, char *window_name, t_fdf *fdf)
{
	fdf->mlx = null_exit(mlx_init(w_width, w_height, window_name, true));
	fdf->img[0] = null_exit(mlx_new_image(fdf->mlx, w_width, w_height));
	fdf->img[1] = null_exit(mlx_new_image(fdf->mlx, w_width, w_height));
	fdf->img_idx[0] = mlx_image_to_window(fdf->mlx, fdf->img[0], 0, 0);
	fdf->img_idx[1] = mlx_image_to_window(fdf->mlx, fdf->img[1], 0, 0);
	exit_if_true(fdf->img_idx[0] < 0 || fdf->img_idx[1] < 0);
	mlx_set_instance_depth(&fdf->img[1]->instances[fdf->img_idx[1]], 1);
	exit_if_true(!mlx_loop_hook(fdf->mlx, loop_hook, fdf));
	mlx_resize_hook(fdf->mlx, resize_hook, fdf);
	mlx_key_hook(fdf->mlx, key_hook, fdf);
	fdf->text_img[0] = null_exit(\
		mlx_put_string(fdf->mlx, "W,A,S,D = move", 10, 10));
	fdf->text_img[1] = null_exit(\
		mlx_put_string(fdf->mlx, "R,F     = zoom", 10, 35));
	fdf->text_img[2] = null_exit(\
		mlx_put_string(fdf->mlx, "T,G     = z-scale", 10, 60));
	fdf->text_img[3] = null_exit(\
		mlx_put_string(fdf->mlx, "P       = projection", 10, 85));
}

t_fdf	*init_fdf(int w_width, int w_height, char *mapfile)
{
	t_fdf	*fdf;
	char	*window_name;

	fdf = null_exit(ft_calloc(1, sizeof(t_fdf)));
	fdf->map = parse_map(mapfile);
	fdf->update = 1;
	fdf->z_scale = 0.5;
	fdf->map_scale = fdf_smallest((float)w_width / 2 / fdf->map->column_count, \
		(float)w_height / 2 / fdf->map->row_count);
	fdf->scale = fdf->map_scale;
	window_name = null_exit(ft_strjoin("FdF: ", mapfile));
	init_mlx(w_width, w_height, window_name, fdf);
	free(window_name);
	return (fdf);
}

void	start_renderloop_fdf(t_fdf *fdf)
{
	mlx_loop(fdf->mlx);
}

void	destroy_fdf(t_fdf *fdf)
{
	destroy_map(fdf->map);
	mlx_delete_image(fdf->mlx, fdf->img[0]);
	mlx_delete_image(fdf->mlx, fdf->img[1]);
	mlx_delete_image(fdf->mlx, fdf->text_img[0]);
	mlx_delete_image(fdf->mlx, fdf->text_img[1]);
	mlx_delete_image(fdf->mlx, fdf->text_img[2]);
	mlx_delete_image(fdf->mlx, fdf->text_img[3]);
	mlx_terminate(fdf->mlx);
	free(fdf);
}
