#include <stdio.h>
#include <stdlib.h>		 // malloc free
#include <unistd.h>		 // write usleep
#include <pthread.h>
#include <sys/time.h>	 // gettimeofday
#include <limits.h>		 // INT_MAX

// already defined in stdlib.h
// #define EXIT_FAILURE 1;
// #define EXIT_SUCCESS 0;
#define DEBUG_MODE 1
#define FAILURE -1
#define SUCCESS 0

typedef	pthread_mutex_t t_mtx;
typedef struct s_table t_table;
// DELETE LATER
// opcode for mutex | threads

typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;


//KEEP
//FORK
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;	
}		t_fork;

// PHILO
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	int			full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mtx		philo_mutex;
	pthread_t	thread_id;
	t_table		*table;
}		t_philo;

// TABLE

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	int		end_simulation;
	int		all_threads_ready;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*forks;
	t_philo	*philos;
};

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
} t_time_code;

// PHILO states

typedef enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

//utils.c
void	precise_usleep(long usec, t_table *table);
long	gettime(t_time_code time_code);

// parsing.c
int	parse_input(t_table *table, char **argv);
int	data_init(t_table *table);

// getters_setters.c
int	simulation_finished(t_table *table);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
int	get_bool(t_mtx *mutex, int *value);
void	set_bool(t_mtx *mutex, int *dest, int value);

// synchro_utils.c
long	gettime(t_time_code time_code);
void	wait_all_threads(t_table *table);
// write.c
void	write_status(t_philo_status status, t_philo *philo, int debug);
// static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed);
// dinner.c
void	dinner_start(t_table *table);