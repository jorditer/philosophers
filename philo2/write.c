/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:30:00 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/28 17:54:04 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
        printf("%ld philo %d has taken as 1° fork the: %d\n", elapsed, philo->id, 
               philo->first_fork->fork_id);
    else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
        printf("%ld philo %d has taken as 2° fork the: %d\n", elapsed, philo->id, 
               philo->second_fork->fork_id);
    else if (EATING == status && !simulation_finished(philo->table))
        printf("%ld %d is eating %ld\n", elapsed, philo->id, philo->meals_counter);
    else if (SLEEPING == status && !simulation_finished(philo->table))
        printf("%ld %d is sleeping\n", elapsed, philo->id);
    else if (THINKING == status && !simulation_finished(philo->table))
        printf("%ld %d is thinking\n", elapsed, philo->id);
    else if (DIED == status)
        printf("%ld %d died\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, int debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (philo->full)
		return ;
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf("%ld: %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf("%ld %d died\n", elapsed, philo->id);
	}
	pthread_mutex_unlock(&philo->table->write_mutex);
}
