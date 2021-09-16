/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:15:27 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/16 17:31:02 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

#include <stdio.h>

static void	sync(void *arg)
{
	t_philo_arg		*p;

	p = (t_philo_arg *)arg;
	pthread_mutex_lock(p->global->gamelock);
	++(p->global->ready);
	pthread_mutex_unlock(p->global->gamelock);
	while (p->global->gamestate == 2)
		;
}

static void	take_fork(void	*arg, int fork_id)
{
	pthread_mutex_lock(((t_philo_arg *)arg)->global->forks[fork_id]);
	print_msg(((t_philo_arg *)arg)->global, ((t_philo_arg *)arg)->id,
		"has taken a fork");
}

static void	eat(void *arg)
{
	print_msg(((t_philo_arg *)arg)->global, ((t_philo_arg *)arg)->id,
		"is eating");
	((t_philo_arg *)arg)->last_meal = get_unix_time();
	go_sleep(((t_philo_arg *)arg)->global->etime);
}

void	*philo_job(void *arg)
{
	sync(arg);
	((t_philo_arg *)arg)->last_meal = ((t_philo_arg *)arg)->global->start;
	while (fetch_gamestate(((t_philo_arg *)arg)->global))
	{
		if (((t_philo_arg *)arg)->id % 2)

	}
	return (NULL);
}
