#ifndef LINE_H
# define LINE_H
# include "fdf.h"

typedef void	(*t_plot_f)(int, int, int, void *);

# define R 3
# define G 2
# define B 1
# define A 0

typedef struct s_line
{
	int			p0[2];
	int			p1[2];
	int			delta[2];
	int			sign[2];
	int			error[2];
	int			color;
	double			color_add[4];
}	t_line;

void	draw_line(t_point p1, t_point p2, \
		void (*plotf)(int, int, int, void *), void *data);

#endif
