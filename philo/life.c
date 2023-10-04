/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:14:57 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/04 15:15:34 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print_action(t_philo *philo, long start, long current, char *s)
{
	long	time;

	time = current - start;
	usleep(200);
	pthread_mutex_lock(&philo->ggame->mx_exit);
	if (philo->ggame->exit_game)
	{
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		return;
	}
	pthread_mutex_unlock(&philo->ggame->mx_exit);
	pthread_mutex_lock(&philo->ggame->mx_print);
	printf("%zu	%d %s\n", time, philo->id, s);
	pthread_mutex_unlock(&philo->ggame->mx_print);
}

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
	while (timestamp() - start < t_action)
	{
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		usleep(100);
	}
}

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
	usleep(50);

	pthread_mutex_lock(&philo->mx_last_meal);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->mx_last_meal);
	
	usleep(500);
	print_action(philo, philo->ggame->start, philo->last_meal, "is eating");
	smart_usleep(philo, philo->params->t_eat);
	pthread_mutex_unlock(&philo->mx_fork);
	pthread_mutex_unlock(&philo->next->mx_fork);
	pthread_mutex_lock(&philo->mx_meals);
	philo->nb_meals += 1;
	pthread_mutex_unlock(&philo->mx_meals);
	return (0);
}

int	sleep_routine(t_philo *philo)
{
	print_action(philo, philo->ggame->start, timestamp(), "is sleeping");
	smart_usleep(philo, philo->params->t_sleep);
	return (0);
}

void	*life_routine(void *args)
{
	int		i;
	t_philo *philo;

	i = 0;
	philo = NULL;
	philo = args;
	if (philo->id % 2 == 0)
	{
		usleep(100);
		print_action(philo, philo->ggame->start, timestamp(), "is thinking");
	}
	while (1)
	{
		pthread_mutex_lock(&philo->ggame->mx_exit);
		if (philo->ggame->exit_game == true)
		{
			pthread_mutex_unlock(&philo->ggame->mx_exit);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		eat_routine(philo);
		if (philo->params->n_philo == 1)
			return (0);
		sleep_routine(philo);
		print_action(philo, philo->ggame->start, timestamp(), "is thinking");
		usleep(100);
	}
	return (NULL);
}
