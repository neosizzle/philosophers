#include "philo.h"

int	ft_atoi(char *nptr)
{
	size_t	offset;
	int		res;
	int		sign;

	offset = 0;
	res = 0;
	sign = 1;
	while (nptr[offset] == ' ' || nptr[offset] == '\n' || nptr[offset] == '\t'
		|| nptr[offset] == '\r' || nptr[offset] == '\v' || nptr[offset] == '\f')
		offset++;
	if (nptr[offset] == '-' || nptr[offset] == '+')
	{
		if (nptr[offset] == '-')
			sign = -1;
		offset++;
	}
	while (nptr[offset] >= '0' && nptr[offset] <= '9')
		res = res * 10 + (nptr[offset++] - '0');
	return (res * sign);
}