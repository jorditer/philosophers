/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:15:18 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/07 12:31:30 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean_partial_data(t_data *data, int failed_index)
{
	int	i;
	
	i = -1;
	if (data->forks)
	{
		while (++i < failed_index)
			pthread_mutex_destroy(&(data->forks[i].fork));
	}
	free(data->forks);
	data->forks = NULL;
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

void	clean_data(t_data *data)
{
	int		i;
	
	if (!data)
		return ;
	if (data->philos)
	{
		i = -1;
		while(++i < data->philo_nbr)
			pthread_mutex_destroy(&(data->philos[i].philo_mutex));
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		i = -1;
		while(++i < data->philo_nbr)
			pthread_mutex_destroy(&(data->forks[i].fork));
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
}