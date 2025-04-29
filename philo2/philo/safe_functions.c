/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:23:29 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 15:24:05 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int safe_pthread(int result, t_table *table)
{
    if (result != 0)
    {
        set_bool(&table->table_mutex, &table->end_simulation, 1);
        return FAILURE;
    }
    return SUCCESS;
}

int safe_mutex_init(pthread_mutex_t *mutex, t_table *table)
{
    return safe_pthread(pthread_mutex_init(mutex, NULL), table);
}

int safe_mutex_destroy(pthread_mutex_t *mutex, t_table *table)
{
    return safe_pthread(pthread_mutex_destroy(mutex), table);
}

int safe_mutex_lock(pthread_mutex_t *mutex, t_table *table)
{
    return safe_pthread(pthread_mutex_lock(mutex), table);
}

int safe_mutex_unlock(pthread_mutex_t *mutex, t_table *table)
{
    return safe_pthread(pthread_mutex_unlock(mutex), table);
}