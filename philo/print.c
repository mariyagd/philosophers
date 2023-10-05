/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:56:13 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/05 09:50:31 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	print_at_start(t_philo *philo, long start, long current, char *s)
{
	long	time;

	time = current - start;
	pthread_mutex_lock(&philo->ggame->mx_print);
	printf("%zu	%d %s\n", time, philo->id, s);
	pthread_mutex_unlock(&philo->ggame->mx_print);
	return (true);
}

bool	print_action(t_philo *philo, long start, long current, char *s)
{
	long	time;

	time = current - start;
	pthread_mutex_lock(&philo->ggame->mx_exit);
	if (philo->ggame->exit_game)
	{
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		return (false);
	}
	pthread_mutex_unlock(&philo->ggame->mx_exit);
	pthread_mutex_lock(&philo->ggame->mx_print);
	printf("%zu	%d %s\n", time, philo->id, s);
	pthread_mutex_unlock(&philo->ggame->mx_print);
	return (true);
}
