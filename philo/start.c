/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:20:04 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/03 22:51:55 by jterrada         ###   ########.fr       */
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

int	dinner_start(t_data *data)
{
	if (data->nbr_limit_meals == 0)
		return (FAILURE);
	else if (data->philo_nbr == 1)
		// TODO;
	else
	{

	}
		
}