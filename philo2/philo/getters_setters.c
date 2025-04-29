/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:50:58 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 22:51:07 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_bool(t_mtx *mutex, int *dest, int value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (FAILURE);
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	get_bool(t_mtx *mutex, int *value)
{
	int	ret;

	if (pthread_mutex_lock(mutex) != 0)
		return (FAILURE);
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (FAILURE);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	if (pthread_mutex_lock(mutex) != 0)
		return (-2);
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (-2);
	return (ret);
}

int	set_long(t_mtx *mutex, long *dest, long value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (FAILURE);
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
