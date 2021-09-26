/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:19:05 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/26 14:02:54 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

#include <stdio.h>

void	set_gamestate(t_global *global, int newval)
{
	pthread_mutex_lock(&(global->gamelock));
	global->gamestate = newval;
	pthread_mutex_unlock(&(global->gamelock));
}

int	fetch_gamestate(t_global *global)
{
	int		x;

	pthread_mutex_lock(&(global->gamelock));
	x = global->gamestate;
	pthread_mutex_unlock(&(global->gamelock));
	return (x);
}

void	print_msg(t_philo_arg *arg, const char *restrict msg)
{
	pthread_mutex_lock(&(arg->global->printer));
	printf("%llu %d %s\n", get_unix_time() - arg->global->start, arg->id + 1,
		msg);
	pthread_mutex_unlock(&(arg->global->printer));
}
