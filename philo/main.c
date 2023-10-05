/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:26:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/04 15:17:02 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

/* In set_game() I malloc philo and create
 * a circular linked list. 
 * t_game structure point to that list.
 *
 * In set_ggame_in_philo() I set the philo
 * structure to point to the t_game structure
 *
 * In this way the structure points to each other
 */

void	set_ggame_in_philo(t_game *game, t_philo *philo)
{
	t_philo	*ptr;
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

void	free_and_destroy(t_game *game)
{
	free_philo_circular_list(&game->philo, game->params.n_philo);
	pthread_mutex_destroy(&game->mx_exit);
	pthread_mutex_destroy(&game->mx_last_meal);
	pthread_mutex_destroy(&game->mx_count);
	pthread_mutex_destroy(&game->mx_print);
}

int	main(int ac, char **av)
{
	t_game		game;

	if (set_game(&game, ac, av) == FAILURE)
		return (1);
	set_ggame_in_philo(&game, game.philo);
	create_threads(&game);
	free_and_destroy(&game);
	return (0);
}
