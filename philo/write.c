/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:05:35 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/07 11:40:18 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	bool	finished;

	simulation_finished(philo->data, &finished);
    if (TAKE_FIRST_FORK == status && !finished)
        printf(W"%6ld"RST" %d has taken the 1° fork 🍴"
            "\t\t\t"B"[ %d ]"RST, elapsed, philo->id,
            philo->first_fork->fork_id);
    else if (TAKE_SECOND_FORK == status && !finished)
        printf(W"%6ld"RST" %d has taken the 2° fork 🍴"
            "\t\t\t"B"[ %d ]"RST, elapsed, philo->id,
            philo->second_fork->fork_id);
    else if (EATING == status && !finished)
        printf(W"%6ld"C" %d is eating 🍝"
            "\t\t\t"Y"[ %ld 🍽️ ]"RST, elapsed, philo->id, philo->meals_count);
    else if (SLEEPING == status && !finished)
        printf(W"%6ld"M" %d is sleeping 😴\n"RST, elapsed, philo->id);
    else if (THINKING == status && !finished)
        printf(W"%6ld"RST" %d is thinking 🤔\n"RST, elapsed, philo->id);
    else if (DIED == status)
        printf(RED"\t⚰️💀 %6ld %d died 💀⚰️\n"RST, elapsed, philo->id);
}

int	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	bool	finished;
	long	elapsed;

	if (simulation_finished(philo->data, &finished) == FAILURE)
		return (FAILURE);
	gettime(MILLISECOND, &elapsed);
	elapsed -= philo->data->start_simulation; //TODO CHECK IF OK
	if (philo->full) // TODO printf is full
		return (SUCCESS);
	if (pthread_mutex_lock(&philo->data->write_mutex) != 0)
		return (FAILURE);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !finished)
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !finished)
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !finished)
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !finished)
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if (DIED == status && !finished)
			printf("%ld %d died\n", elapsed, philo->id);
	}
	if (pthread_mutex_unlock(&philo->data->write_mutex) != 0)
		return (FAILURE);
	return (SUCCESS);

}