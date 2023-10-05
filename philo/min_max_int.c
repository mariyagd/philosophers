/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:05:12 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/05 12:28:53 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	positive_long_check(char *str)
{
	char	*s_long_max;
	int		len;

	if (!str)
		return (FAILURE);
	s_long_max = "+9223372036854775807";
	len = ft_strlen(str);
	if (len > 20)
		return (FAILURE);
	if (len == 20 && ft_strncmp(s_long_max, str, 20) < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	long_check(char *str)
{
	char	*s_long_max;
	int		len;

	s_long_max = "9223372036854775807";
	if (!str)
		return (FAILURE);
	len = ft_strlen(str);
	if (len > 19)
		return (FAILURE);
	if (len == 19 && ft_strncmp(s_long_max, str, 19) < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	positive_int_check(char *str)
{
	char	*s_int_max;
	int		len;

	if (!str)
		return (FAILURE);
	s_int_max = "+2147483647";
	len = ft_strlen(str);
	if (len > 11)
		return (FAILURE);
	if (len == 11 && ft_strncmp(s_int_max, str, 11) < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	int_check(char *str)
{
	char	*s_int_max;
	int		len;

	s_int_max = "2147483647";
	if (!str)
		return (FAILURE);
	len = ft_strlen(str);
	if (len > 10)
		return (FAILURE);
	if (len == 10 && ft_strncmp(s_int_max, str, 10) < 0)
		return (FAILURE);
	return (SUCCESS);
}
