/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:19:05 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/16 17:57:15 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

#include <stdio.h>

void	set_gamestate(t_global *global, int newval)
{
	pthread_mutex_lock(global->gamelock);
	global->gamestate = newval;
	pthread_mutex_unlock(global->gamelock);
}

int	fetch_gamestate(t_global *global)
{
	int		x;

	pthread_mutex_lock(global->gamelock);
	x = global->gamestate;
	pthread_mutex_unlock(global->gamelock);
	return (x);
}

void	print_msg(t_global *global, int id, const char *restrict msg)
{
	pthread_mutex_lock(global->printer);
	printf("%llu %d %s\n", get_unix_time() - global->start, id, msg);
	pthread_mutex_unlock(global->printer);
}
