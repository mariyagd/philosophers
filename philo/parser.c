/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:25:09 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/06 12:35:18 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	negative_or_invalid_argument(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			printf("Error: invalid argument\n");
			return ;
		}
		i++;
	}
	if (i == 0)
		printf("Error: invalid argument\n");
	else
		printf("Error: all arguments must be positive\n");
	return ;
}

int	helper(char **av, int i, int j)
{
	if (j == 0 && av[i][j] == '-')
	{
		negative_or_invalid_argument(&av[i][j + 1]);
		return (FAILURE);
	}
	if (j == 0 && av[i][j] == '+')
	{
		if (av[i][j + 1] == '\0')
		{
			printf("Error: invalid argument\n");
			return (FAILURE);
		}
		return (SUCCESS);
	}
	else
	{
		printf("Error: invalid argument\n");
		return (FAILURE);
	}
}

int	is_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				if (helper(av, i, j) == FAILURE)
					return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	parse_arguments(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: invalid number of arguments\n");
		return (FAILURE);
	}
	if (is_digit(av) == FAILURE)
		return (FAILURE);
	if (whitin_min_max(ac, av) == FAILURE)
		return (FAILURE);
	if (ft_atoi(av[1]) < 1)
	{
		printf("Error: number of philosophers must be at least 1\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
