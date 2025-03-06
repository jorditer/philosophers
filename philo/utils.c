/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:36:11 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/06 14:04:36 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// struct timeval
// {
// #ifdef __USE_TIME_BITS64
//   __time64_t tv_sec;		/* Seconds.  */
//   __suseconds64_t tv_usec;	/* Microseconds.  */
// #else
//   __time_t tv_sec;		/* Seconds.  */
//   __suseconds_t tv_usec;	/* Microseconds.  */
// #endif
// };
// #endif
int	gettime(t_time_code time_code, long *time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (FAILURE);
	else if (SECOND == time_code)
		*time = (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		*time = (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		*time = (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		return (FAILURE);
	return (SUCCESS);
}

// remaining > 1e3 (1ms) (usleep / 2) as there's no need to be precise
// else spinlock (repeated checks), which is more precise but CPU intensive
int	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	time;
	bool	finished;
	long	elapsed;
	long	remaining;

	if (gettime(MICROSECOND, &start) == FAILURE || gettime(MICROSECOND, &time))
		return (FAILURE);
	finished = false;
	while (time - start < usec)
	{
		gettime(MICROSECOND, &time);
		if (simulation_finished(data, &finished == FAILURE))
			return (FAILURE);
		if (finished)
			break ;
		elapsed = time - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			// SPINLOCK
			while (time - start < usec)
				;
		}
	}
	return (SUCCESS);
}
