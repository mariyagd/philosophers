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
	printf("rb meals = %d\n", params->max_meals);
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
		params->meal_rule= ft_atoi(av[5]);
	else
		params->meal_rule = NO_RULE;
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
	if (pthread_mutex_init(&game->mx_next, NULL) < 0)
	{
		printf("Error: pthread_mutex_init: mx_print\n");
		free_philo_circular_list(&game->philo, game->params.n_philo);
		return(FAILURE);
	}
	if (pthread_mutex_init(&game->mx_exit, NULL) < 0)
	{
		printf("Error: pthread_mutex_init: mx_print\n");
		free_philo_circular_list(&game->philo, game->params.n_philo);
		return(FAILURE);
	}
	game->dead = false;
	game->meals_counter = 0;
	game->exit_game = false;
	game->philo_id = 0;
	return (SUCCESS);
}

void	set_ggame(t_game *game, t_philo *philo)
{
	t_philo *ptr;
	int		i;

	ptr = NULL;
	i = 0;
	ptr = philo;
	while (i < game->params.n_philo)
	{
		ptr->ggame = game;
		ptr = ptr->next;
		i++;
	}
}

int main(int ac, char **av)
{
	t_game		game;

	set_game(&game, ac, av);
	set_ggame(&game, game.philo);
	create_threads(&game);
	free_philo_circular_list(&game.philo, game.params.n_philo);
	return (0);
}

