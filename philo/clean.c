/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:15:18 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/06 10:36:40 by jterrada         ###   ########.fr       */
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

void	clean_data(t_data **data)
{

}