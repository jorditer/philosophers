/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:49:59 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 23:16:29 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

static int	eat(t_philo *philo)
{
	if (safe_mutex_lock(&philo->first_fork->fork, philo->table) == FAILURE)
		return (FAILURE);
	write_status(TAKE_FIRST_FORK, philo);
	if (safe_mutex_lock(&philo->second_fork->fork, philo->table) == FAILURE)
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		return (FAILURE);
	}
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, 1);
	if (safe_mutex_unlock(&philo->first_fork->fork, philo->table) == FAILURE)
	{
		pthread_mutex_unlock(&philo->second_fork->fork);
		return (FAILURE);
	}
	if (safe_mutex_unlock(&philo->second_fork->fork, philo->table) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	de_syncronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		eat(philo);
		if (simulation_finished(philo->table) || get_bool(&philo->philo_mutex,
				&philo->full))
			break ;
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, 0);
	}
	return (NULL);
}

// else if is the corner case of one philosopher
static int	create_philo_threads(t_table *table)
{
	int	i;

	i = -1;
	if (table->philo_nbr == 1)
	{
		if (safe_thread_create(&table->philos[0].thread_id, lone_philo,
				&table->philos[0], table) == FAILURE)
			return (FAILURE);
	}
	else
	{
		while (++i < table->philo_nbr)
		{
			if (safe_thread_create(&table->philos[i].thread_id,
					dinner_simulation, &table->philos[i], table) == FAILURE)
			{
				set_bool(&table->table_mutex, &table->end_simulation, 1);
				while (--i >= 0)
					pthread_join(table->philos[i].thread_id, NULL);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

int	dinner_start(t_table *table)
{
	int	i;

	if (table->nbr_limit_meals == 0)
		return (SUCCESS);
	if (create_philo_threads(table) == FAILURE)
		return (FAILURE);
	if (safe_thread_create(&table->monitor, monitor_dinner, table,
			table) == FAILURE)
	{
		set_bool(&table->table_mutex, &table->end_simulation, 1);
		return (FAILURE);
	}
	if (set_bool(&table->table_mutex, &table->all_threads_ready, 1) == FAILURE)
		return (FAILURE);
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (safe_thread_join(table->philos[i].thread_id, table) == FAILURE)
		{
			set_bool(&table->table_mutex, &table->end_simulation, 1);
			return (FAILURE);
		}
	}
	set_bool(&table->table_mutex, &table->end_simulation, 1);
	return (safe_thread_join(table->monitor, table));
}
