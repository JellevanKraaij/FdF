/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 17:00:21 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/03/24 17:00:21 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc < 2 || argc > 2)
	{
		ft_putendl_fd("fdf: incorrect parameter", STDERR_FILENO);
		ft_putendl_fd("usage: ./fdf [file]", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	fdf = init_fdf(1000, 1000, argv[1]);
	start_renderloop_fdf(fdf);
	destroy_fdf(fdf);
	return (EXIT_SUCCESS);
}
