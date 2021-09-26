/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:18:56 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/26 16:10:59 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void	select__(t_philo_arg *args, int *q, int turn)
{
	int			i;

	i = args[0].global->nphilo / 2;
	turn = (turn + 1) % args[0].global->nphilo;
	while (i--)
	{
		q[i] = turn;
		turn = (turn + 2) % args[0].global->nphilo;
	}
}

static void	sync__(t_philo_arg *arg)
{
	pthread_mutex_lock(&(arg[0].global->gamelock));
	++(arg[0].global->ready);
	pthread_mutex_unlock(&(arg[0].global->gamelock));
	while (arg[0].global->gamestate == 2)
		;
}

static void	init(void *arg, t_philo_arg **p, int *turn, int **q)
{
	int	i;

	(*p) = (t_philo_arg *)arg;
	i = (*p)[0].global->nphilo;
	*turn = i - 1;
	(*q) = (int *)malloc(sizeof(int) * ((*p)->global->nphilo / 2));
	while (i--)
		pthread_mutex_lock(&((*p)[i].action));
}

// this does not cause undefined behaviour
// as after gameover all mutexes are in locked state
// and owned by current waiter thread
static void	release(t_philo_arg *arg, int *q)
{
	int	i;

	i = arg[0].global->nphilo;
	while (i--)
		pthread_mutex_unlock(&(arg[i].action));
	free(q);
}

//arg is pointer to philo args
void	*waiter_job(void *arg)
{
	t_philo_arg		*p;
	int				turn;
	int				i;
	int				*q;

	init(arg, &p, &turn, &q);
	sync__(p);
	if (p[0].global->nphilo == 1)
		return (NULL);
	while (fetch_gamestate(p[0].global))
	{
		select__(p, q, turn);
		i = (p[0].global->nphilo / 2);
		while (i--)
			pthread_mutex_unlock(&p[q[i]].action);
		go_sleep(p[0].global->etime);
		i = (p[0].global->nphilo / 2);
		while (i--)
			pthread_mutex_lock(&p[q[i]].action);
		turn = (turn + 1) % p[0].global->nphilo;
	}
	release(p, q);
	return (NULL);
}
