/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:19 by jterrada          #+#    #+#             */
/*   Updated: 2025/04/29 15:32:36 by jterrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int safe_thread_create(pthread_t *thread, void *(*routine)(void *), 
                      void *arg, t_table *table)
{
    return safe_pthread(pthread_create(thread, NULL, routine, arg), table);
}

int safe_thread_join(pthread_t thread, t_table *table)
{
    return safe_pthread(pthread_join(thread, NULL), table);
}