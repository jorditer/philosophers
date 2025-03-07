/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:20:04 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/07 15:09:38 by jterrada         ###   ########.fr       */
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
// EAT
// 1) GRAB FORKS 2) EAT (update meal) 3) RELEASE FORKS
// Take forks write status / eating updating time and eat status
// sleep for the amount of time requested check if we reach meals_count == nbr_l_meals

int thinking(t_philo *philo)
{
	if (write_status(THINKING, philo, DEBUG_MODE) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	eat(t_philo *philo)
{
	long time;
	
    printf("Philo %d trying for forks %d and %d\n",  // DELETE
		philo->id, philo->first_fork->fork_id, philo->second_fork->fork_id); // DELETE

	if (gettime(MILLISECOND, &time) == FAILURE
		|| pthread_mutex_lock(&philo->first_fork->fork) != 0	
		|| write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE) == FAILURE	
		|| pthread_mutex_lock(&philo->second_fork->fork) != 0	
		|| write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE) == FAILURE
		|| set_long(&philo->philo_mutex, &philo->last_meal_time, time) == FAILURE
		|| write_status(EATING, philo, DEBUG_MODE) == FAILURE
		|| precise_usleep(philo->data->time_to_eat, philo->data) == FAILURE)
		return (FAILURE);
	philo->meals_count++;
	if (philo->data->nbr_limit_meals > 0
		&& philo->meals_count == philo->data->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	if (pthread_mutex_unlock(&philo->first_fork->fork) != 0
		|| pthread_mutex_unlock(&philo->second_fork->fork) != 0)
		{
			printf("Philo %d failed at eating\n", philo->id); // DELETE
			return (FAILURE);
		}
	return (SUCCESS);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	bool finished;

	philo = (t_philo *)data;
	wait_threads(philo->data);
	finished = false;
	while (!finished)
	{
		if (simulation_finished(philo->data, &finished) == FAILURE)
    		return ((void *)FAILURE);
		if (philo->full)
			break ;
		// EAT
		if (eat(philo) == FAILURE)
    		return ((void *)FAILURE);
		// SLEEP
		write_status(SLEEPING, philo, DEBUG_MODE);
		if (precise_usleep(philo->data->time_to_sleep, philo->data) == FAILURE)
    		return ((void *)FAILURE);
		// THINK
		thinking(philo);
	}
	return (NULL);
}

int	dinner_start(t_data *data)
{
	int	i;
	
	i = -1;
	if (data->nbr_limit_meals == 0)
		return (FAILURE);
	else if (data->philo_nbr == 1)
		return (FAILURE); // TODOO;
	else
	{
		while (++i < data->philo_nbr)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL,
				dinner_simulation, &data->philos[i]) != 0)
				return (FAILURE);
		}
	}
	if (gettime(MILLISECOND, &data->start_simulation) == FAILURE)
		return (FAILURE);
	set_bool(&data->data_mutex, &data->threads_ready, true);
	i = -1;
	while(++i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (FAILURE);
	}
	return (SUCCESS);
}