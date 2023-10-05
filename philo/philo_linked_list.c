/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:04:17 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/05 09:09:48 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

/* if (i != 0) means if this philo
 * is not the head of the linked list
 *
 * If this is a philo in the middle
 * of the linked list, I free it,
 * return Failure, and then free the linked list
 */

int	init_philo_mutex(t_philo *philo, int i)
{
	if (pthread_mutex_init(&philo->mx_fork, NULL) < 0)
	{
		printf("Error: pthread_mutex_init for fork [%d]\n", i);
		if (i != 0)
			free(philo);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_philo	*create_philo(int i, t_params *params)
{
	t_philo	*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
	{
		printf("Error: malloc");
		return (NULL);
	}
	if (init_philo_mutex(philo, i) == FAILURE)
		return (NULL);
	philo->id = i + 1;
	philo->params = params;
	philo->ate_all_meals = false;
	return (philo);
}

void	create_circular_list(t_philo **list)
{
	t_philo	*head;
	t_philo	*last;

	head = NULL;
	last = NULL;
	head = *list;
	last = *list;
	while (last)
	{
		if (last && !last->next)
			break ;
		last = last->next;
	}
	last->next = head;
}

/*
* Creation of circular linked list of philos
* even if the number of philos is 1
*/

int	set_philos(t_philo **head, t_params *params)
{
	int		i;
	t_philo	*next_philo;
	t_philo	*current_philo;

	i = 0;
	*head = create_philo(i, params);
	if (!*head)
		return (FAILURE);
	current_philo = *head;
	i = 1;
	while (i < params->n_philo)
	{
		if (i != 1)
			current_philo = current_philo->next;
		next_philo = create_philo(i, params);
		if (!next_philo)
		{
			free_philo_linear_list(head);
			return (FAILURE);
		}
		current_philo->next = next_philo;
		i++;
	}
	create_circular_list(head);
	return (SUCCESS);
}
