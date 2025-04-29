/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:58:35 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 23:17:15 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if errors, assume not dead (return (0));
static int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;
	long	last_meal;
	int		is_full;

	last_meal = get_long(&philo->philo_mutex, &philo->last_meal_time);
	if (last_meal == -2)
		return (0);
	elapsed = gettime(MILLISECOND) - last_meal;
	if (elapsed == 0)
		return (0);
	t_to_die = philo->table->time_to_die / 1e3;
	is_full = get_bool(&philo->philo_mutex, &philo->full);
	if (is_full == FAILURE)
		return (0);
	if (is_full)
		return (0);
	if (elapsed > t_to_die)
		return (1);
	return (0);
}

// if one get_bool is false then all_full = false;
static int	all_philos_full(t_table *table)
{
	int	i;
	int	all_full;

	i = -1;
	all_full = 1;
	while (++i < table->philo_nbr)
	{
		if (!get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
		{
			all_full = 0;
			break ;
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
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while ((!simulation_finished(table)))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i) && !simulation_finished(table))
			{
				set_bool(&table->table_mutex, &table->end_simulation, 1);
				write_status(DIED, table->philos + i);
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
