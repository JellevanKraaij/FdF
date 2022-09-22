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

typedef struct s_mappoint {
	int	height;
	int	color;
}	t_mappoint;

typedef struct s_2dmap {
	t_list	*elements;
	size_t	row_len;
}	t_2dmap;

t_2dmap		*parse_map(char *filename);

t_mappoint	*init_mappoint(void);
t_mappoint	*create_mappoint(int heigt, int color);

t_2dmap		*init_2dmap(void);
t_2dmap		*create_2dmap(t_list *elements, int row_len);

int			ft_atoi_p(const char *str, int *number);

void		perror_exit(const char *s, int error_code) \
					__attribute__((noreturn));
void		*null_exit(void	*ptr);

#endif
