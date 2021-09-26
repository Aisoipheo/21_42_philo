/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:18:56 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/26 14:29:03 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static void	sync__(t_philo_arg *arg)
{
	pthread_mutex_lock(&(arg[0].global->gamelock));
	++(arg[0].global->ready);
	pthread_mutex_unlock(&(arg[0].global->gamelock));
	while (arg[0].global->gamestate == 2)
		;
}

static void	init(void *arg, t_philo_arg **p, int *turn)
{
	int	i;

	(*p) = (t_philo_arg *)arg;
	i = (*p)[0].global->nphilo;
	*turn = 0;
	while (i--)
		pthread_mutex_lock(&((*p)[i].action));
}

// this does not cause undefined behaviour
// as after gameover all mutexes are in locked state
// and owned by current waiter thread
static void	release(t_philo_arg *arg)
{
	int	i;

	i = arg[0].global->nphilo;
	while (i--)
		pthread_mutex_unlock(&(arg[i].action));
}

//arg is pointer to philo args
void	*waiter_job(void *arg)
{
	t_philo_arg		*p;
	int				turn;
	int				i;

	init(arg, &p, &turn);
	sync__(p);
	if (p[0].global->nphilo == 1)
		return (NULL);
	while (fetch_gamestate(p[0].global))
	{
		i = -1;
		while (++i < p[0].global->nphilo)
			if (i % 2 == turn)
				pthread_mutex_unlock(&(p[i].action));
		go_sleep(p[0].global->etime);
		i = -1;
		while (++i < p[0].global->nphilo)
			if (i % 2 == turn)
				pthread_mutex_lock(&(p[i].action));
		turn = (turn + 1) % 2;
	}
	release(p);
	return (NULL);
}
