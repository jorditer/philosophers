#include "philo.h"

// while threads not ready don't start
void	wait_all_threads(t_table *table)
{
	while(!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

int all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
		ret = 1;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	increase_long(t_mtx *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

void	de_syncronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, 1);
	}
}