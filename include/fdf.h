/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helloworld.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 23:41:24 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/03/30 23:41:24 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>

typedef struct s_3dpoint {
	int	height;
	int	color;
}	t_3dpoint;

typedef struct s_2dpoint {
	int	color;
	int	x;
	int	y;
}	t_2dpoint;

typedef struct s_map {
	t_list	*elements;
	size_t	row_count;
	size_t	column_count;
}	t_map;

t_map		*parse_map(char *filename);

t_3dpoint	*init_3dpoint(void);
t_3dpoint	*create_3dpoint(int heigt, int color);
void		destroy_3dpoint(void *mappoint);

t_2dpoint	*init_2dpoint(void);
t_2dpoint	*create_2dpoint(int color, int x, int y);
void		destroy_2dpoint(void *mappoint);

t_map		*init_map(void);
void		destroy_map(t_map *map);

int			ft_atoi_safe(const char *str, int *number);

void		perror_exit(const char *s, int error_code) \
					__attribute__((noreturn));
void		*null_exit(void	*ptr);
void		print_error_exit(char *error, int error_code) \
					__attribute__((noreturn));
void		print_error(char *error);

#endif
