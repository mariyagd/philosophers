#include "philo.h"
#include <pthread.h>


void	*checker_routine(void	*args)
{
	t_game	*game;

	game = NULL;
	game = args;
	while (1)
	{
		pthread_mutex_lock(&game->mx_exit);
		if (game->exit_game == false)
			{
				pthread_mutex_unlock(&game->mx_exit);
				break;
			}
		pthread_mutex_lock(&game->philo->mx_dead);
		if (game->philo->dead == false)
		{
			pthread_mutex_lock(&game->mx_exit);
			game->exit_game = true;
			pthread_mutex_unlock(&game->mx_exit);
		}
		pthread_mutex_unlock(&game->philo->mx_dead);
		if (game->params.meal_rule != NO_RULE)
		{
			pthread_mutex_lock(&game->philo->mx_meals);
			if (game->philo->nb_meals == game->params.meal_rule)
			{
				game->meals_counter += 1;
			}
			pthread_mutex_unlock(&game->philo->mx_meals);
			if (game->meals_counter == game->params.meal_rule)
				game->exit_game = true;
		}
		pthread_mutex_lock(&game->mx_next);
		game->philo = game->philo->next;
		pthread_mutex_unlock(&game->mx_next);
	}
	return (NULL);
}

int	create_threads(t_game *game)
{
	int			i;

	i = 0;
	game->start = timestamp();
	while (i < game->params.n_philo)
	{
		game->philo->last_meal = game->start;
		game->philo = game->philo->next;
		i++;
	}
	i = 0;
	game->philo = game->philo->next;
	while (i < game->params.n_philo)
	{
		pthread_create(&game->philo->thread, NULL, life_routine, (void *)game->philo);
		game->philo = game->philo->next;
		i++;
	}
	game->philo = game->philo->next;
	pthread_create(&game->checker, NULL, checker_routine, (void *)game);
	i = 0;
	while (i < game->params.n_philo)
	{
		pthread_mutex_lock(&game->mx_next);
		pthread_join(game->philo->thread, NULL);
		game->philo = game->philo->next;
		pthread_mutex_unlock(&game->mx_next);
		i++;
	}
	pthread_join(game->checker, NULL);
	return (SUCCESS);
}
