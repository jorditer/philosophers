/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:05:13 by jterrada          #+#    #+#             */
/*   Updated: 2025/03/03 22:10:35 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
// {
	
// }

int	safe_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (*ptr == NULL)
		return (FAILURE);
	return (SUCCESS);
}