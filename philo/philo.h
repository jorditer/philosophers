/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:06:39 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/03 22:17:31 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
// #include <limits.h>

#ifndef PHILO_H
# define PHILO_H

#define INT_MAX 0x7fffffff
#define SUCCESS 1
#define FAILURE 0
// enum
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;
// structs
typedef struct s_data t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;

}	t_fork;

// Each philosopher is a thread
typedef struct s_philo
{
	int			id;
	long		meals_count;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;

}	t_data;

// checks.c
int		check_args(int argc, char **argv);
int		is_num(char c);
int		is_whitespace(char c);
// parsing.c
int		parse_input(t_data *data, int argc, char **argv);
// init.c
int		data_init(t_data *data);
// safe_functions.c
int		safe_malloc(void **ptr, size_t size);
// start.c

#endif