#include <libft.h>
#include <stdio.h>

static int	ft_chr_num_16(char c)
{
	c = ft_tolower(c);
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (-1);
}

static int	ft_atoi_16(const char *str, int *num, int sign)
{
	long	ret;

	ret = 0;
	while (ft_chr_num_16(*str) >= 0)
	{
		ret = (ret * 16) + ft_chr_num_16(*str);
		if (ret > (long)INT_MAX + 1 || (sign == 1 && ret > INT_MAX))
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	ret *= sign;
	*num = ret;
	return (0);
}

static int	ft_atoi_10(const char *str, int *num, int sign)
{
	long	ret;

	ret = 0;
	while (ft_isdigit(*str))
	{
		ret = (ret * 10) + (*str - '0');
		if (ret > (long)INT_MAX + 1 || (sign == 1 && ret > INT_MAX))
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	ret *= sign;
	*num = ret;
	return (0);
}

int	ft_atoi_safe(const char *str, int *number)
{
	int		sign;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (ft_strncmp(str, "0x", 2) == 0)
		return (ft_atoi_16(str + 2, number, sign));
	return (ft_atoi_10(str, number, sign));
}
