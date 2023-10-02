#include "philo.h"

t_philo	*create_philo(int i, t_params *params)
{
	t_philo	*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
	{
		printf("Error: malloc");
		return (NULL);
	}
	if (pthread_mutex_init(&philo->l_fork, NULL) < 0)
	{
		printf("Error: pthread_mutex_init for fork [%d]\n", i);
		if (i != 0)
			free(philo);
		return (NULL);
	}
	philo->id = i;
	philo->params = params;
	return (philo);
}

void	free_philo_list(t_philo **head)
{
	t_philo	*current;
	t_philo	*next;

	current = *head;
	next = NULL;
	while (current)
	{
		next = current->next;
		pthread_mutex_destroy(&current->l_fork);
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
		pthread_mutex_destroy(&current->l_fork);
		free(current);
		current = next;
		i++;
	}
	head = NULL;
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
			break;
		last = last->next;
	}
	last->next = head;
}

int	set_philos(t_philo **head, t_params *params)
{
	int		i;
	t_philo	*next_philo;
	t_philo	*current_philo;

	i = 1;
	*head = create_philo(0, params);
	if (!*head)
		return (FAILURE);
	current_philo = *head;
	while (i < params->n_philo)
	{
		if (i != 1)
			current_philo = current_philo->next;
		next_philo = create_philo(i, params);
		if (!next_philo)
		{
			free_philo_list(head);
			return (FAILURE);
		}
		current_philo->next = next_philo;
		i++;
	}
	create_circular_list(head);
	return (SUCCESS);
}
