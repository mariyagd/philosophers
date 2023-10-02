/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:29:57 by mdanchev          #+#    #+#             */
/*   Updated: 2023/10/02 09:38:12 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stddef.h>
#include <sys/_pthread/_pthread_mutex_t.h>

# define SUCCESS	1
# define FAILURE	0
# define NO_RULE	-1


typedef struct 					s_params
{
	int							n_philo;
	long						t_die;
	long						t_eat;
	long						t_sleep;
	int							max_meals;

}       						t_params;

typedef struct 					s_philo
{
	int							id;
	pthread_t					thread;
	pthread_mutex_t   			l_fork;
	t_params          			*params;
	struct s_philo 				*next;
}              					t_philo;

typedef struct 					s_game 
{
	t_params					params;
	t_philo						*philo;
	pthread_mutex_t				mx_print;
}								t_game;

int		parse_arguments(int ac, char **av);
long	ft_atol(char *str);
int		ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);
int		set_philos(t_philo **head, t_params *params);
void	free_philo_circular_list(t_philo **head, int n_philos);

#endif
