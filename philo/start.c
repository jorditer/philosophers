/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:20:04 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/06 12:29:00 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
1 If no meals return
2 If only one philo
3 Create all threads & philos
4 Monitor dead philos
5 Sync the beginning
6 Join all
*/

void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	bool finished;

	philo = (t_philo *)data;
	wait_threads(philo->data);
	finished = false;
	while (!finished)
	{
		if (simulation_finished(philo->data, finished) == FAILURE)
			return (FAILURE);
		if (philo->full)
			break ;
		eat(philo);
		sleep(philo);
		thinking(philo);

	}
	return(NULL);
}

int	dinner_start(t_data *data)
{
	int	i;

	if (data->nbr_limit_meals == 0)
	return (FAILURE);
	else if (data->philo_nbr == 1)
		// TODO;
	i = -1;
	else
	{
		while (++i < data->philo_nbr)
		{
			pthread_create(&data->philos[i].thread_id, NULL, dinner_simulation, &data->philos[i]);
			data->forks[i].fork_id = i;
		}
	}
	set_bool(&data->data_mutex, &data->threads_ready, true);
	i = -1;
	while(++i < data->philo_nbr)
	{
		if (pthread_join(&data->philos[i].thread_id, NULL) != 0);
			return (FAILURE);
	}
}