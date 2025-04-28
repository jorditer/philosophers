/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:15:58 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/28 17:13:48 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// return 1 just to not get a warning
long	gettime(t_time_code time_code)
{
	struct	timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0); // EXIT TODO
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
	if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + (tv.tv_usec));
	return(1);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(usec / 2);
		else
		{
			// SPINLOCK
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}