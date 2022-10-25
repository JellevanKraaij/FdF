/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:58:32 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:58:32 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H
# include "fdf.h"

typedef void	(*t_plot_f)(int, int, int, void *);

# define R 3
# define G 2
# define B 1
# define A 0

typedef struct s_color
{
	double	current[4];
	double	increase[4];
	int		axis;
	int		change;
	int		original;
}	t_color;

typedef struct s_line
{
	int			start[2];
	int			end[2];
	int			delta[2];
	int			sign[2];
	int			error[2];
	t_color		color;
}	t_line;

void	draw_line(t_point p1, t_point p2, \
		void (*plotf)(int, int, int, void *), void *data);

#endif
