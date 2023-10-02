/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:26:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/02 09:29:15 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <pthread.h>

/*
//	check_params_assignement(&params);
void	check_params_assignement(t_params *params)
{
	printf("Nb philo = %d\n", params->n_philo);
	printf("Time to die = %zu\n", params->t_die);
	printf("Time to eat = %zu\n", params->t_eat);
	printf("Time to sleep = %zu\n", params->t_sleep);
	printf("Nb meals = %d\n", params->max_meals);
}

//	check_game(philo);
void	check_game(t_game *game)
{
	t_philo	*ptr;
	int		i;
	int 	max;

	ptr = NULL;
	ptr = game->philos;
	i = 0;
	max = game->params.n_philo;

	while (i < max)
	{
		printf("[%d]---------\n", i);
		check_params_assignement(ptr->params);
		printf("-------------\n");
		ptr = ptr->next;
		i++;
	}
}
*/

void	set_params(t_params *params, int ac, char **av)
{
	params->n_philo = ft_atoi(av[1]);
	params->t_die = ft_atol(av[2]);
	params->t_eat = ft_atol(av[3]);
	params->t_sleep = ft_atol(av[4]);
	if (ac == 6)
		params->max_meals = ft_atoi(av[5]);
	else
		params->max_meals = NO_RULE;
}


void	*life_routine(void *args)
{
	(void)args;
	printf("hello\n");
	return (NULL);
}


int	set_game(t_game *game, int ac, char **av)
{
	if (parse_arguments(ac, av) == FAILURE)
		return (FAILURE);
	set_params(&game->params, ac, av);
	if (set_philos(&game->philo, &game->params) == FAILURE)
		return (FAILURE);
	if (pthread_mutex_init(&game->mx_print, NULL) < 0)
	{
		printf("Error: pthread_mutex_init: mx_print\n");
		free_philo_circular_list(&game->philo, game->params.n_philo);
		return(FAILURE);
	}
	return (SUCCESS);
}

int main(int ac, char **av)
{
	t_game		game;
	t_philo		*head;
	int			i;

	i = 0;
	set_game(&game, ac, av);
	head = game.philo;
	while (i < game.params.n_philo)
	{
		pthread_create(&game.philo->thread, NULL, life_routine, (void *)game.philo);
		game.philo = game.philo->next;
		i++;
	}
	i = 0;
	game.philo = head;
	while (i < game.params.n_philo)
	{
		pthread_join(game.philo->thread, NULL);
		i++;
		game.philo = game.philo->next;
	}
	game.philo = head;
	free_philo_circular_list(&game.philo, game.params.n_philo);
	return (0);
}

