#include "philo.h"

long	ft_atol(char *str)
{
	long	res;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	if (*str == '\0')
		return (-1);
	while (*str && *str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res);
}

int ft_atoi(char *str)
{
	int res;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	if (*str == '\0')
		return (-1);
	while (*str && *str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res);
}
