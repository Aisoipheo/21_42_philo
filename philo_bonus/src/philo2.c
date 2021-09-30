/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:02:30 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/30 12:16:03 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>

static void	*ft_worker(void *arg)
{
	t_worker	*p;

	p = (t_worker *)arg;
	p->is_alive = 1;
	while (p->is_game)
	{
		if (p->id % 2 == 0)
			sleep_think(p);
		sem_wait(p->forks);
		print_msg(p, "has taken a fork");
		sem_wait(p->forks);
		print_msg(p, "has taken a fork");
		if (p->is_game)
			eat(p);
		sem_post(p->forks);
		sem_post(p->forks);
		if (p->is_game && p->id % 2)
			sleep_think(p);
	}
	return (NULL);
}

static char	*get_name(int proc_id)
{
	char	*name;
	size_t	len;
	size_t	i;

	len = my_strlen(PHILO_DEATHLOCK_PREFIX);
	name = (char *)malloc(sizeof(char) * (len + 6));
	i = len;
	while (i--)
		name[i] = PHILO_DEATHLOCK_PREFIX[i];
	i = 5;
	while (i--)
	{
		name[len + i] = proc_id % 10 + '0';
		proc_id /= 10;
	}
	name[len + 5] = '\0';
	sem_unlink(name);
	return (name);
}

static void	monitor(t_worker *w)
{
	while (w->is_alive == 0)
		;
	while (w->is_game)
	{
		sem_wait(w->deathlock);
		if (w->meals >= w->global->neat && w->global->neat > -1)
			w->is_game = 0;
		if ((int)(get_unix_time() - w->last_meal) > w->global->dtime)
		{
			w->is_game = 0;
			print_msg(w, "died");
		}
		sem_post(w->deathlock);
		usleep(100);
	}
	sem_post(w->global->gamelock);
}

int	child_proc(t_global *g, int proc_id)
{
	char			*deathlock_name;
	pthread_t		worker;
	t_worker		arg;

	deathlock_name = get_name(proc_id);
	arg.last_meal = g->start;
	arg.meals = 0;
	arg.id = proc_id;
	arg.deathlock = sem_open(deathlock_name, O_CREAT, 0600, 1);
	arg.is_alive = 0;
	arg.is_game = 1;
	arg.forks = g->forks;
	arg.gamelock = g->gamelock;
	arg.global = g;
	pthread_create(&worker, NULL, ft_worker, &arg);
	monitor(&arg);
	pthread_join(worker, NULL);
	sem_close(arg.deathlock);
	sem_unlink(deathlock_name);
	free(deathlock_name);
	return (EXIT_SUCCESS);
}
