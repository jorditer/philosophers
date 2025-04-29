/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:00:39 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 23:00:40 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*n;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (NULL);
	if (!is_digit(*str))
		return (NULL);
	n = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		return (NULL);
	return (n);
}

// returns -1 as error
static long	ft_atol(const char *str)
{
	long	n;

	n = 0;
	str = valid_input(str);
	if (!str)
		return (FAILURE);
	while (is_digit(*str))
		n = (n * 10) + (*str++ - '0');
	if (n > INT_MAX)
		return (FAILURE);
	if (n < 0)
		return (FAILURE);
	return (n);
}

// returns -1 if there's an error
int	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0 || table->philo_nbr < 0)
		return (FAILURE);
	if (table->time_to_die < 6000 || table->time_to_eat < 6000
		|| table->time_to_sleep < 6000)
		return (FAILURE);
	if (argv[5])
	{
		table->nbr_limit_meals = ft_atol(argv[5]);
		if (table->nbr_limit_meals < 0)
			return (FAILURE);
	}
	else
		table->nbr_limit_meals = -1;
	return (SUCCESS);
}
