/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:15:27 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/22 12:01:01 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

#include <stdio.h>

static void	sync(void *arg)
{
	t_philo_arg		*p;

	p = (t_philo_arg *)arg;
	pthread_mutex_lock(&(p->global->gamelock));
	++(p->global->ready);
	pthread_mutex_unlock(&(p->global->gamelock));
	while (p->global->gamestate == 2)
		;
}

static void	sleep_think(void *arg)
{
	print_msg(((t_philo_arg *)arg)->global, (((t_philo_arg *)arg)->id + 1),
		"is sleeping");
	go_sleep(((t_philo_arg *)arg)->global->stime);
	if (fetch_gamestate(((t_philo_arg *)arg)->global))
		print_msg(((t_philo_arg *)arg)->global, (((t_philo_arg *)arg)->id + 1),
			"is thinking");
}

static void	take_fork(void	*arg, int fork_id)
{
	pthread_mutex_lock(&(((t_philo_arg *)arg)->global->forks[fork_id]));
	if (fetch_gamestate(((t_philo_arg *)arg)->global))
		print_msg(((t_philo_arg *)arg)->global, (((t_philo_arg *)arg)->id + 1),
			"has taken a fork");
}

static void	eat(void *arg)
{
	pthread_mutex_lock(&((t_philo_arg *)arg)->deathlock);
	++((t_philo_arg *)arg)->meals;
	print_msg(((t_philo_arg *)arg)->global, (((t_philo_arg *)arg)->id + 1),
		"is eating");
	((t_philo_arg *)arg)->last_meal = get_unix_time();
	pthread_mutex_unlock(&((t_philo_arg *)arg)->deathlock);
	go_sleep(((t_philo_arg *)arg)->global->etime);
}

void	*philo_job(void *arg)
{
	t_philo_arg		*p;

	p = (t_philo_arg *)arg;
	pthread_mutex_lock(&(p->deathlock));
	sync(arg);
	p->last_meal = p->global->start;
	pthread_mutex_unlock(&(p->deathlock));
	while (fetch_gamestate(p->global) && p->global->nphilo > 1)
	{
		if (p->id % 2)
			sleep_think(arg);
		take_fork(arg, p->id);
		take_fork(arg, (p->id + 1) % p->global->nphilo);
		if (fetch_gamestate(p->global))
			eat(arg);
		pthread_mutex_unlock(&(p->global->forks[p->id]));
		pthread_mutex_unlock(&(p->global->forks[(p->id + 1)
				% p->global->nphilo]));
		if (p->id % 2 == 0 && fetch_gamestate(p->global))
			sleep_think(arg);
	}
	return (NULL);
}
