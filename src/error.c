/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 19:58:47 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/25 19:58:47 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

void	*null_exit(void	*ptr)
{
	if (ptr != NULL)
		return (ptr);
	perror_exit("fdf", 1);
}

void	perror_exit(const char *s, int error_code)
{
	perror(s);
	exit(error_code);
}

void	print_error_exit(char *error, int error_code)
{
	print_error(error);
	exit(error_code);
}

void	print_error(char *error)
{
	ft_putstr_fd("fdf: ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
}
