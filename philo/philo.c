/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:56:26 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/03 22:17:35 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]
// ./philo 1/num_of_philo 2/time_to_die 3/time_to_eat 4/time_to_sleep 5/num_to_full

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

int	main(int argc, char **argv)
{
	t_data data;
	
	if (!(argc == 5 || argc == 6))
		return (1);
	//1 parse_input
	if (!parse_input(&data, argc, argv))
		return (1);
		
	//2 create the thing
	if (!data_init(&data))
		return (1);

	//3 start simulation

	//4 clean (philos full or 1 died)

	printf("test");
	return (0);
}