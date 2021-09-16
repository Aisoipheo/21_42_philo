/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:19:05 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/16 16:44:18 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
