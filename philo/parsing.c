/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:39:55 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/07 14:49:26 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ./philo 5 800 200 200 [5]
// ./philo 1/num_of_philo 2/time_to_die 3/time_to_eat 4/time_to_sleep 5/num_to_full

#include "philo.h"

int valid_input(const char **str)
{
	int			len;
	const char	*number;

	while (is_whitespace(**str))
		(*str)++;
	if (**str == '+')
		(*str)++;
	else if (**str == '-')
		return (0);
	if (!is_num(**str))
		return (0);
	number = *str;
	while (is_num(*number))
	{
		len++;
		number++;
	}
	if (len > 10)
		return (0);
	return (1);
}

// if atol returns -1 then there has been an error
static long ft_atol(const char *str)
{
	long num;

	num = 0;
	valid_input(&str);
	while (is_num(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (num > INT_MAX)
		return (-1);
	return (num);
}

// returns 0 if there was an error 1 if ok
int	parse_input(t_data *data, int argc, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 60
		|| data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (FAILURE);
	if (argc == 6)
		data->nbr_limit_meals = ft_atol(argv[5]);
	else
		data->nbr_limit_meals = -1;
	return (SUCCESS);
}