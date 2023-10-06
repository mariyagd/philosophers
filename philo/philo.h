/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:29:57 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/06 12:03:30 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/_pthread/_pthread_mutex_t.h>
# include <sys/_pthread/_pthread_t.h>
# include <sys/time.h>

# define SUCCESS	1
# define FAILURE	0
# define NO_RULE	-1

typedef struct s_params
{
	int							n_philo;
	long						t_die;
	long						t_eat;
	long						t_sleep;
	int							meal_rule;
}								t_params;

typedef struct s_philo
{
	int							id;
	int							nb_meals;
	long						last_meal;
	bool						ate_all_meals;
	t_params					*params;
	pthread_t					thread;
	struct s_game				*ggame;
	struct s_philo				*next;
	pthread_mutex_t				mx_fork;
}								t_philo;

typedef struct s_game
{
	int							meals_counter;
	long						start;
	bool						exit_game;
	t_philo						*philo;
	t_params					params;
	pthread_mutex_t				mx_exit;
	pthread_mutex_t				mx_last_meal;
	pthread_mutex_t				mx_count;
	pthread_mutex_t				mx_print;
}								t_game;

int		parse_arguments(int ac, char **av);
long	ft_atol(char *str);
int		ft_atoi(char *str);
int		set_game(t_game *game, int ac, char **av);
void	*ft_calloc(size_t count, size_t size);
int		set_philos(t_philo **head, t_params *params);
void	free_philo_circular_list(t_philo **head, int n_philos);
long	timestamp(void);
long	passed_time(long start);
int		create_threads(t_game *game);
void	*life_routine(void *args);
bool	print_action(t_philo *philo, long start, long current, char *s);
bool	print_at_start(t_philo *philo, long start, long current, char *s);
void	free_philo_circular_list(t_philo **head, int n_philos);
void	free_philo_linear_list(t_philo **head);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		int_check(char *str);
int		positive_int_check(char *str);
int		long_check(char *str);
int		positive_long_check(char *str);
int		whitin_min_max(int ac, char **av);
#endif
