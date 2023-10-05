/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:08:22 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/05 09:08:27 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	free_philo_linear_list(t_philo **head)
{
	t_philo	*current;
	t_philo	*next;

	current = *head;
	next = NULL;
	while (current)
	{
		next = current->next;
		pthread_mutex_destroy(&current->mx_fork);
		free(current);
		current = next;
	}
	head = NULL;
}

void	free_philo_circular_list(t_philo **head, int n_philos)
{
	t_philo	*current;
	t_philo	*next;
	int		i;

	i = 0;
	current = *head;
	next = NULL;
	while (i < n_philos)
	{
		next = current->next;
		pthread_mutex_destroy(&current->mx_fork);
		free(current);
		current = next;
		i++;
	}
	head = NULL;
}
