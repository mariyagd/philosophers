/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:14:57 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/05 09:47:31 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	smart_usleep(t_philo *philo, long t_action)
{
	long	start;

	start = timestamp();
	pthread_mutex_lock(&philo->ggame->mx_exit);
	if (philo->ggame->exit_game == true)
	{
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		return ;
	}
	pthread_mutex_unlock(&philo->ggame->mx_exit);
	usleep(100);
	while (timestamp() - start < t_action)
	{
		usleep(50);
	}
}

/*	if (print_action(philo, philo->ggame->start, timestamp(), \
 *								"has taken a fork") == false)
	{
		pthread_mutex_unlock(&philo->mx_fork);
		pthread_mutex_unlock(&philo->next->mx_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->ggame->mx_meal);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->ggame->mx_meal);
	if (print_action(philo, philo->ggame->start, philo->last_meal, \
											"is eating") == false)
	{
		pthread_mutex_unlock(&philo->mx_fork);
		pthread_mutex_unlock(&philo->next->mx_fork);
		return (0);
	}
*/

int	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->mx_fork);
	print_action(philo, philo->ggame->start, timestamp(), "has taken a fork");
	if (philo->params->n_philo == 1)
	{
		pthread_mutex_unlock(&philo->mx_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->next->mx_fork);
	print_action(philo, philo->ggame->start, timestamp(), "has taken a fork");
	pthread_mutex_lock(&philo->ggame->mx_last_meal);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->ggame->mx_last_meal);
	print_action(philo, philo->ggame->start, philo->last_meal, "is eating");
	smart_usleep(philo, philo->params->t_eat);
	pthread_mutex_unlock(&philo->mx_fork);
	pthread_mutex_unlock(&philo->next->mx_fork);
	pthread_mutex_lock(&philo->ggame->mx_count);
	philo->nb_meals += 1;
	pthread_mutex_unlock(&philo->ggame->mx_count);
	return (0);
}

void	sleep_routine(t_philo *philo)
{
	print_action(philo, philo->ggame->start, timestamp(), "is sleeping");
	smart_usleep(philo, philo->params->t_sleep);
	return ;
}

bool	exit_game(t_philo *philo)
{
	pthread_mutex_lock(&philo->ggame->mx_exit);
	if (philo->ggame->exit_game == true)
	{
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		return (true);
	}
	pthread_mutex_unlock(&philo->ggame->mx_exit);
	return (false);
}

void	*life_routine(void *args)
{
	t_philo	*philo;

	philo = NULL;
	philo = args;
	if (philo->id % 2 == 0)
	{
		print_at_start(philo, philo->ggame->start, timestamp(), "is thinking");
		usleep(200);
	}
	while (1)
	{
		if (exit_game(philo) == true)
			return (NULL);
		eat_routine(philo);
		if (philo->nb_meals == 0)
			return (NULL);
		sleep_routine(philo);
		print_action(philo, philo->ggame->start, timestamp(), "is thinking");
	}
	return (NULL);
}
