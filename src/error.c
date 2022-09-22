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
