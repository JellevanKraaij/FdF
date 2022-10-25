#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <MLX42/MLX42.h>

# define X 0
# define Y 1
# define Z 2
# define ISO 0

typedef struct s_point
{
	double	cords[3];
	int		color;
}	t_point;

typedef struct s_map {
	t_point		*points;
	size_t		row_count;
	size_t		column_count;
}	t_map;

typedef struct s_fdf {
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			update;
	double		scale;
	double		map_scale;
	double		z_scale;
	double		x_offset;
	double		y_offset;
	int			projection;
}	t_fdf;

t_fdf	*init_fdf(int w_width, int w_height, char *mapfile);
void	start_renderloop_fdf(t_fdf *fdf);
void	destroy_fdf(t_fdf *fdf);

void	update_screen(t_fdf *data);
void	key_hook(mlx_key_data_t keydata, void *data_p);
void	resize_hook(int32_t width, int32_t height, void *data_p);
void	loop_hook(void *data_p);

t_map	*init_map(void);
t_map	*parse_map(char *filename);
void	destroy_map(t_map *map);
t_map	*dup_map(t_map *map);

void	map_project_iso(t_map *map);
void	map_apply_scale(t_map *map, double scale[3]);
void	map_apply_offset(t_map *map, double offset[3]);
void	plot_lines(mlx_image_t *img, t_map *map);
void	plot_line(mlx_image_t *img, t_point point1, t_point point2);
void	plot_point(mlx_image_t *img, t_map *map);

int		ft_atoi_safe(const char *str, int *number);
void	perror_exit(const char *s, int error_code) \
				__attribute__((noreturn));
void	*null_exit(void	*ptr);
void	print_error_exit(char *error, int error_code) \
					__attribute__((noreturn));
void	print_error(char *error);

#endif
