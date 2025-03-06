/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:54:04 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/06 12:28:40 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{ 
	if (pthread_mutex_lock(mutex) != 0)
		return (FAILURE);
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	get_bool(pthread_mutex_t *mutex, bool *source, bool *dest)
{ 
	if (pthread_mutex_lock(mutex) != 0)
		return (FAILURE);
	*dest = *source;
	if (pthread_mutex_unlock(mutex) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	set_long(pthread_mutex_t *mutex, long *dest, long value)
{ 
	if (pthread_mutex_lock(mutex) != 0)
		return (FAILURE);
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	get_long(pthread_mutex_t *mutex, long *source, long *dest)
{ 
	if (pthread_mutex_lock(mutex) != 0)
		return (FAILURE);
	*dest = *source;
	if (pthread_mutex_unlock(mutex) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	simulation_finished(t_data *data, bool *dest)
{
	return(get_bool(&data->data_mutex, &data->end_simulation, dest));
}