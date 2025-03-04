/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:00:00 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/03 22:16:55 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// (philo_position + 1) % philo_nbr for knowing forks
void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->id % 2)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
	
}

// philos + i for pointer arithmetic
void philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->data = data;
		assign_forks(philo, data->forks, i);
	}
}

int	data_init(t_data *data)
{
	int i;

	data->end_simulation = false;
	if (!safe_malloc((void **)&data->philos, sizeof(t_philo) * data->philo_nbr)
		|| !safe_malloc((void **)&data->forks, sizeof(t_fork) * data->philo_nbr))
		return (FAILURE);
	i = -1;
	while (++i < data->philo_nbr)
	{
		if (!pthread_mutex_init(&data->forks[i].fork, NULL))
			return (FAILURE);
		data->forks[i].fork_id = i;
	}
	return (SUCCESS);
}
