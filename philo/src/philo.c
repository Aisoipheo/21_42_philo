/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:16:05 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/09 16:32:32 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlist.h"
#include "philo.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

static void	parse_argv(t_args *args, int argc, char *argv[])
{
	my_atoi(argv[1], &args->nphilo);
	my_atoi(argv[2], &args->dtime);
	my_atoi(argv[3], &args->etime);
	my_atoi(argv[4], &args->stime);
	if (argc == 6)
		my_atoi(argv[5], &args->neat);
	else
		args->neat = -1;
}

static void	init(pthread_t **t, pthread_mutex_t **m,
				t_args *args, t_philo_arg **p)
{
	int		i;

	*t = (pthread_t *)malloc(sizeof(pthread_t) * args->nphilo);
	*m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->nphilo);
	*p = (t_philo_arg *)malloc(sizeof(t_philo_arg) * args->nphilo);
	i = 0;
	while (i < args->nphilo)
	{
		pthread_mutex_init(&(*m)[i], NULL);
		(*p)[i].id = i;
		(*p)[i].mutexes = *m;
		(*p)[i].args = args;
	}
}

static void	simulate(pthread_t **t, t_args *args, t_philo_arg **p)
{
	int		i;

	i = 0;
	while (i < args->nphilo)
		pthread_create(&(*t[i]), NULL, philo_job, &(*p)[i]);
}

static void	destroy(pthread_t **t, pthread_mutex_t **m,
					t_args *args, t_philo_arg **p)
{
	int		i;

	i = 0;
	while (i < args->nphilo)
	{
		pthread_join(&(*t)[i], NULL);
		pthread_mutex_destroy(&(*m)[i]);
		++i;
	}
	free(*t);
	free(*m);
	free(*p);
}

int	main(int argc, char *argv[])
{
	t_args				args;
	pthread_t			*threads;
	pthread_mutex_t		*mutexes;
	t_philo_arg			*philo_args;

	if (argc != 5 && argc != 6)
		return (1);
	parse_argv(&args, argc, argv);
	init(&threads, &mutexes, &args, &philo_args);
	simulate(&threads, &args, &philo_args);
	destroy(&threads, &mutexes, &args, &philo_args);
	return (0);
}
