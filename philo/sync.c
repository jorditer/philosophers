/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:42:38 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/06 11:54:20 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_threads(t_data *data)
{
	bool ready;

	ready = false;
	while(!ready)
	{
		if (!get_bool(&data->data_mutex, &data->threads_ready, &ready))
			return (FAILURE);
	}
	return (SUCCESS);

}