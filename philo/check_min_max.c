/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_min_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:05:12 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/05 12:33:58 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	check_min_max_helper1(char *str, int i)
{
	if (i == 1 || i == 5)
	{
		if (positive_int_check(str) == FAILURE)
		{
			printf("Error: argument %d is greater than int max\n", i);
			return (FAILURE);
		}
	}
	else
	{
		if (positive_long_check(str) == FAILURE)
		{
			printf("Error: argument %d is greater than long max\n", i);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	check_min_max_helper2(char *str, int i)
{
	if (i == 1 || i == 5)
	{
		if (int_check(str) == FAILURE)
		{
			printf("Error: argument %d is greater than int max\n", i);
			return (FAILURE);
		}
	}
	else
	{
		if (long_check(str) == FAILURE)
		{
			printf("Error: argument %d is greater than long max\n", i);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	check_min_max(char *str, int i)
{
	if (!str)
		return (FAILURE);
	if (str[0] == '+')
	{
		if (check_min_max_helper1(str, i) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (check_min_max_helper2(str, i) == FAILURE)
			return (FAILURE);
	}
	return (1);
}

int	whitin_min_max(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (check_min_max(av[i], i) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
