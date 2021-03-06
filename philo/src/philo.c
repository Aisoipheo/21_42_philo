/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:16:05 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/26 14:00:51 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static int	parse_argv(t_global *args, int argc, char *argv[])
{
	my_atoi(argv[1], &args->nphilo);
	my_atoi(argv[2], &args->dtime);
	my_atoi(argv[3], &args->etime);
	my_atoi(argv[4], &args->stime);
	if (argc == 6)
		my_atoi(argv[5], &args->neat);
	else
		args->neat = -1;
	if (args->nphilo <= 0 || args->dtime < 0
		|| args->etime < 0 || args->stime < 0)
		return (1);
	return (0);
}

static void	init(pthread_t **t,
				t_global *args, t_philo_arg **p)
{
	int		i;

	*t = (pthread_t *)malloc(sizeof(pthread_t) * (args->nphilo + 1));
	args->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* args->nphilo);
	*p = (t_philo_arg *)malloc(sizeof(t_philo_arg) * args->nphilo);
	pthread_mutex_init(&(args->gamelock), NULL);
	pthread_mutex_init(&(args->printer), NULL);
	args->gamestate = 2;
	args->ready = 0;
	i = args->nphilo;
	while (i--)
	{
		pthread_mutex_init(&(args->forks[i]), NULL);
		pthread_mutex_init(&(*p)[i].deathlock, NULL);
		pthread_mutex_init(&(*p)[i].action, NULL);
		(*p)[i].id = i;
		(*p)[i].global = args;
		(*p)[i].meals = 0;
		pthread_create(&(*t)[i], NULL, philo_job, &(*p)[i]);
	}
	pthread_create(&(*t)[args->nphilo], NULL, waiter_job, (*p));
	while (args->ready != (args->nphilo + 1))
		usleep(25);
}

static void	monitor(t_global *args, t_philo_arg **p)
{
	int		i;
	int		f;

	args->start = get_unix_time();
	args->gamestate = 1;
	while (fetch_gamestate(args))
	{
		usleep(100);
		i = args->nphilo;
		f = 1;
		while (i--)
		{
			pthread_mutex_lock(&(*p)[i].deathlock);
			f = !((*p)[i].meals < args->neat) && f;
			if ((int)(get_unix_time() - (*p)[i].last_meal) > args->dtime)
			{
				set_gamestate(args, 0);
				print_msg(&(*p)[i], "died");
			}
			pthread_mutex_unlock(&(*p)[i].deathlock);
		}
		if (f && args->neat > -1)
			set_gamestate(args, 0);
	}
}

static void	destroy(pthread_t *t,
					t_global *global, t_philo_arg **p)
{
	int		i;

	i = global->nphilo + 1;
	while (i--)
		pthread_join(t[i], NULL);
	i = global->nphilo;
	while (i--)
	{
		pthread_mutex_destroy(&(global->forks[i]));
		pthread_mutex_destroy(&(*p)[i].deathlock);
		pthread_mutex_destroy(&(*p)[i].action);
	}
	pthread_mutex_destroy(&(global->gamelock));
	pthread_mutex_destroy(&(global->printer));
	free(t);
	free(*p);
	free(global->forks);
}

int	main(int argc, char *argv[])
{
	t_global			global;
	pthread_t			*threads;
	t_philo_arg			*philo_args;

	if (argc != 5 && argc != 6)
		return (1);
	if (parse_argv(&global, argc, argv))
		return (1);
	init(&threads, &global, &philo_args);
	monitor(&global, &philo_args);
	destroy(threads, &global, &philo_args);
	return (0);
}
