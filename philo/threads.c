/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:13:07 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/05 09:48:41 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	check_all_ate(t_game *game, t_philo *philo)
{
	if (philo->ate_all_meals == false)
	{
		pthread_mutex_lock(&game->mx_count);
		if (philo->nb_meals >= game->params.meal_rule)
		{
			game->meals_counter += 1;
			philo->ate_all_meals = true;
		}
		pthread_mutex_unlock(&game->mx_count);
	}
	if (game->meals_counter == game->params.n_philo)
	{
		pthread_mutex_lock(&game->mx_exit);
		game->exit_game = true;
		pthread_mutex_unlock(&game->mx_exit);
		return (true);
	}
	return (false);
}

void	checker_routine(t_game *game)
{
	while (1)
	{
		pthread_mutex_lock(&game->mx_last_meal);
		if (timestamp() - game->philo->last_meal > game->params.t_die)
		{
			pthread_mutex_unlock(&game->mx_last_meal);
			print_action(game->philo, game->start, timestamp(), "died");
			pthread_mutex_lock(&game->mx_exit);
			game->exit_game = true;
			pthread_mutex_unlock(&game->mx_exit);
			return ;
		}
		pthread_mutex_unlock(&game->mx_last_meal);
		if (game->params.meal_rule != NO_RULE && game->params.n_philo > 1)
		{
			if (check_all_ate(game, game->philo) == true)
				return ;
		}
		if (game->params.n_philo > 1)
			game->philo = game->philo->next;
		usleep (100);
	}
	return ;
}

int	create_threads(t_game *game)
{
	int			i;

	i = 0;
	game->start = timestamp();
	game->philo = game->philo->next;
	while (i < game->params.n_philo)
	{
		game->philo->last_meal = timestamp();
		pthread_create(&game->philo->thread, NULL, life_routine, \
													(void *)game->philo);
		game->philo = game->philo->next;
		i++;
	}
	game->philo = game->philo->next;
	checker_routine(game);
	i = 0;
	while (i < game->params.n_philo)
	{
		pthread_join(game->philo->thread, NULL);
		game->philo = game->philo->next;
		i++;
	}
	return (SUCCESS);
}
