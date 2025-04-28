#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	table->start_simulation = gettime(MILLISECOND);
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_counter = 0;
		philo->table = table;
		pthread_mutex_init(&philo->philo_mutex, NULL);
		assign_forks(philo, table->forks, i);
	}
}

int	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = 0;
	table->all_threads_ready = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	pthread_mutex_init(&table->table_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	if (!table->philos)
		return (FAILURE);
	while(++i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	return (1); // does this function return something?? check why
}