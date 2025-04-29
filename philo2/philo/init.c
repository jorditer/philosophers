/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:51:22 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 23:10:14 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// The if cleans up previously initialized mutexes
static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	table->start_simulation = gettime(MILLISECOND);
	if (table->start_simulation == 0)
		return (FAILURE);
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_counter = 0;
		philo->table = table;
		if (safe_mutex_init(&philo->philo_mutex, table) == FAILURE)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->philos[i].philo_mutex);
			return (FAILURE);
		}
		assign_forks(philo, table->forks, i);
	}
	return (SUCCESS);
}

static int	init_table_resources(t_table *table)
{
	table->end_simulation = 0;
	table->all_threads_ready = 0;
	table->threads_running_nbr = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (FAILURE);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
	{
		free(table->philos);
		return (FAILURE);
	}
	if (safe_mutex_init(&table->table_mutex, table) == FAILURE
		|| safe_mutex_init(&table->write_mutex, table) == FAILURE)
	{
		free(table->philos);
		free(table->forks);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	data_init(t_table *table)
{
	int	i;

	if (init_table_resources(table) == FAILURE)
		return (FAILURE);
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (safe_mutex_init(&table->forks[i].fork, table) == FAILURE)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i].fork);
			pthread_mutex_destroy(&table->table_mutex);
			pthread_mutex_destroy(&table->write_mutex);
			free(table->philos);
			free(table->forks);
			return (FAILURE);
		}
		table->forks[i].fork_id = i;
	}
	if (philo_init(table) == FAILURE)
	{
		clean(table);
		return (FAILURE);
	}
	return (SUCCESS);
}
