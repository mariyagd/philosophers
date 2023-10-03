#include "philo.h"
#include <pthread.h>

void	print_action(t_philo *philo, long start, long current, char *s)
{
	long	time;
/*	(void)s;
	(void)philo;
	printf(" start = %zu, current = %zu", start, current);*/
	
	time = current - start;
	pthread_mutex_lock(&philo->ggame->mx_print);
	printf("%zu	%d %s\n", time, philo->id, s);
	pthread_mutex_unlock(&philo->ggame->mx_print);
}

void	smart_usleep(t_philo *philo, long t_action)
{
	long	timeto_die;
	long	time_slept;
	long	start;

	start = timestamp();
	timeto_die = passed_time(philo->last_meal);
	time_slept = timestamp() - start;
	while (time_slept < t_action)
	{
		pthread_mutex_lock(&philo->ggame->mx_exit);
		if (philo->ggame->exit_game == true)
			return ;
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		usleep(100);
		timeto_die = passed_time(philo->last_meal);
		time_slept = timestamp() - start;
		if (timeto_die >= philo->params->t_die)
		{
			pthread_mutex_lock(&philo->mx_dead);
			philo->dead = true;
			pthread_mutex_unlock(&philo->mx_dead);
			pthread_mutex_lock(&philo->ggame->mx_exit);
			philo->ggame->exit_game = true;
			pthread_mutex_unlock(&philo->ggame->mx_exit);
			print_action(philo, philo->ggame->start, timestamp(), "has died");
			return ;
		}
	}
}

int	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->mx_fork);
	print_action(philo, philo->ggame->start, timestamp(), "has taken a fork");
	pthread_mutex_lock(&philo->next->mx_fork);
	print_action(philo, philo->ggame->start, timestamp(), "has taken a fork");
	philo->last_meal = timestamp();
	print_action(philo, philo->ggame->start, philo->last_meal, "is eating");
	smart_usleep(philo, philo->params->t_eat);
	pthread_mutex_unlock(&philo->mx_fork);
	pthread_mutex_unlock(&philo->next->mx_fork);
	if (philo->params->meal_rule != 0)
	{
		pthread_mutex_lock(&philo->mx_meals);
		philo->nb_meals += 1;
		pthread_mutex_lock(&philo->mx_meals);
	}
	return (0);
}

int	sleep_routine(t_philo *philo)
{
	print_action(philo, philo->ggame->start, timestamp(), "is sleeping");
	smart_usleep(philo, philo->params->t_sleep);
	return (0);
}

void	*life_routine(void *args)
{
	int		i;
	t_philo *philo;

	i = 0;
	philo = NULL;
	philo = args;
	if (philo->id % 2 != 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->ggame->mx_exit);
		if (philo->ggame->exit_game == true)
			break ;
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		print_action(philo, philo->ggame->start, timestamp(), "is thinking");
		pthread_mutex_lock(&philo->ggame->mx_exit);
		if (philo->ggame->exit_game == true)
			break ;
		pthread_mutex_unlock(&philo->ggame->mx_exit);
		eat_routine(philo);
		sleep_routine(philo);
	}
	return (NULL);
}
