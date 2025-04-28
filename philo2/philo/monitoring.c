#include "philo.h"

static int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return (0);
	if (elapsed > t_to_die)
		return (1);
	return (0);
}

static int all_philos_full(t_table *table)
{
	int i;
	int all_full;

	i = -1;
	all_full = 1;
	while (++i < table->philo_nbr)
	{
		if (!get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
		{
			all_full = 0; // At least one philosopher is not full
			break;
		}
	}
	return (all_full);
}

// printf("All philosophers have eaten %ld meals each. Simulation ending.\n", 
// 	table->nbr_limit_meals); // put inside the innermost if
void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while(!all_threads_running(&table->table_mutex, &table->threads_running_nbr,
		table->philo_nbr))
		;

	while ((!simulation_finished(table)))
	{
		i = -1;
		while(++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i) && !simulation_finished(table))
			{
				set_bool(&table->table_mutex, &table->end_simulation, 1);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
			if (table->nbr_limit_meals > 0 && all_philos_full(table) 
			&& !simulation_finished(table))
			{
				set_bool(&table->table_mutex, &table->end_simulation, 1);
			}
		}
	}
	return (NULL);
}