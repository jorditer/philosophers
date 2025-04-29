/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:01:34 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 23:01:35 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5];
// ~/.venv/c-formatter/bin/c_formatter_42 your_file.c
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&table, argv) == FAILURE)
			return (EXIT_FAILURE);
		if (data_init(&table) == FAILURE)
			return (EXIT_FAILURE);
		if (dinner_start(&table) == FAILURE)
		{
			clean(&table);
			return (EXIT_FAILURE);
		}
		clean(&table);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
