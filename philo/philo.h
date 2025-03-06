/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:06:39 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/06 15:05:09 by jterrada         ###   ########.fr       */
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


// debug for write
#define DEBUG_MODE 0
// colors
#define W "\033[1;37m"
#define RST "\033[0m"
#define B "\033[1;34m"
#define C "\033[1;36m"
#define Y "\033[1;33m"
#define M "\033[1;35m"
#define RED "\033[1;31m"

#define INT_MAX 0x7fffffff
#define SUCCESS 1
#define FAILURE 0
// enum
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

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
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_limit_meals;
	long			start_simulation;
	bool			end_simulation;
	bool			threads_ready;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	write_mutex;
	t_fork			*forks;
	t_philo			*philos;

}	t_data;
// CODES FOR GETTIME

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

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

//utils.c
int		gettime(t_time_code time_code, long *time);
void	precise_usleep(long usec, t_data *data);
// setters.c
int	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
int	get_bool(pthread_mutex_t *mutex, bool *source, bool *dest);
int	set_long(pthread_mutex_t *mutex, long *dest, long value);
int	get_long(pthread_mutex_t *mutex, long *source, long *dest);
int	simulation_finished(t_data *data, bool *dest);
// write.c
int	write_status(t_philo_status status, t_philo *philo, bool debug);
// sync.c
int	wait_threads(t_data *data);

#endif