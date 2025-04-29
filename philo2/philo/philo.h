/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:02:37 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 23:16:55 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> // INT_MAX
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>   // malloc free
#include <sys/time.h> // gettimeofday
#include <unistd.h>   // write usleep

// already defined in stdlib.h
// #define EXIT_FAILURE 1;
// #define EXIT_SUCCESS 0;
#define DEBUG_MODE 0
#define FAILURE -1
#define SUCCESS 0

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
// DELETE LATER
// opcode for mutex | threads

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

// KEEP
// FORK
typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

// PHILO
typedef struct s_philo
{
	int					id;
	long				meals_counter;
	int					full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_mtx				philo_mutex;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

// TABLE

struct					s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	int					end_simulation;
	int					all_threads_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
};

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

// PHILO states

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

// utils.c
void					precise_usleep(long usec, t_table *table);
long					gettime(t_time_code time_code);
void					clean(t_table *table);

// parsing.c
int						parse_input(t_table *table, char **argv);
int						data_init(t_table *table);

// getters_setters.c
int						simulation_finished(t_table *table);
int						set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
int						get_bool(t_mtx *mutex, int *value);
int						set_bool(t_mtx *mutex, int *dest, int value);

// synchro_utils.c
long					gettime(t_time_code time_code);
void					wait_all_threads(t_table *table);
int						all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					de_syncronize_philos(t_philo *philo);
void					increase_long(t_mtx *mutex, long *value);
// write.c
void					write_status(t_philo_status status, t_philo *philo);
// dinner.c
int						dinner_start(t_table *table);
void					thinking(t_philo *philo, int pre_simulation);
// monitoring.c
void					*monitor_dinner(void *data);
// safe_functions.c
int						safe_pthread(int result, t_table *table);
;
int						safe_mutex_init(pthread_mutex_t *mutex, t_table *table);
int						safe_mutex_destroy(pthread_mutex_t *mutex,
							t_table *table);
int						safe_mutex_lock(pthread_mutex_t *mutex, t_table *table);
int						safe_mutex_unlock(pthread_mutex_t *mutex,
							t_table *table);

// safe_functions2.c
int						safe_thread_create(pthread_t *thread,
							void *(*routine)(void *), void *arg,
							t_table *table);
int						safe_thread_join(pthread_t thread, t_table *table);
