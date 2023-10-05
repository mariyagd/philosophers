/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:12:15 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/05 09:24:22 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	init_game_mutex_helper(t_game *game)
{
	if (pthread_mutex_init(&game->mx_last_meal, NULL) < 0)
	{
		printf("Error: pthread_mutex_init: game->mx_last_meal\n");
		pthread_mutex_destroy(&game->mx_print);
		pthread_mutex_destroy(&game->mx_exit);
		free_philo_circular_list(&game->philo, game->params.n_philo);
		return (FAILURE);
	}
	if (pthread_mutex_init(&game->mx_count, NULL) < 0)
	{
		printf("Error: pthread_mutex_init: game->mx_count\n");
		pthread_mutex_destroy(&game->mx_print);
		pthread_mutex_destroy(&game->mx_exit);
		pthread_mutex_destroy(&game->mx_last_meal);
		free_philo_circular_list(&game->philo, game->params.n_philo);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_game_mutex(t_game *game)
{
	if (pthread_mutex_init(&game->mx_print, NULL) < 0)
	{
		printf("Error: pthread_mutex_init: game->mx_print\n");
		free_philo_circular_list(&game->philo, game->params.n_philo);
		return (FAILURE);
	}
	if (pthread_mutex_init(&game->mx_exit, NULL) < 0)
	{
		printf("Error: pthread_mutex_init: game->mx_exit\n");
		pthread_mutex_destroy(&game->mx_print);
		free_philo_circular_list(&game->philo, game->params.n_philo);
		return (FAILURE);
	}
	if (init_game_mutex_helper(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	set_params(t_params *params, int ac, char **av)
{
	params->n_philo = ft_atoi(av[1]);
	params->t_die = ft_atol(av[2]);
	params->t_eat = ft_atol(av[3]);
	params->t_sleep = ft_atol(av[4]);
	if (ac == 6)
		params->meal_rule = ft_atoi(av[5]);
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
	if (init_game_mutex(game) == FAILURE)
		return (FAILURE);
	game->meals_counter = 0;
	game->exit_game = false;
	return (SUCCESS);
}
