#include "philo.h"
#include <pthread.h>

bool	check_all_ate(t_game *game, t_philo *philo)
{
	if (philo->max_meals == false)
	{
		pthread_mutex_lock(&philo->mx_meals);
		if (philo->nb_meals >= game->params.meal_rule)
		{
			game->meals_counter += 1;
			philo->max_meals = true;
		}
		pthread_mutex_unlock(&philo->mx_meals);
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
	long	last;

	last = 0;
	while (1)
	{
		pthread_mutex_lock(&game->philo->mx_last_meal);
		last = game->philo->last_meal;
		pthread_mutex_unlock(&game->philo->mx_last_meal);
		if (timestamp() - last > game->params.t_die)
		{
			print_action(game->philo, game->start, timestamp(), "died");
			pthread_mutex_lock(&game->mx_exit);
			game->exit_game = true;
			pthread_mutex_unlock(&game->mx_exit);
			return ;
		}
		usleep(100);
		if (game->params.meal_rule != NO_RULE \
			&& check_all_ate(game, game->philo) == true \
			&& game->params.n_philo > 1)
			return ;
		if (game->params.n_philo > 1)
			game->philo = game->philo->next;
		usleep(500);
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
		pthread_create(&game->philo->thread, NULL, life_routine, (void *)game->philo);
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
