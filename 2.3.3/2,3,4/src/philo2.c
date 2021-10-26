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
	print_msg(((t_philo_arg *)arg), "is sleeping");
	go_sleep(((t_philo_arg *)arg)->global->stime);
	if (fetch_gamestate(((t_philo_arg *)arg)->global))
		print_msg(((t_philo_arg *)arg), "is thinking");
}

static void	take_fork(void	*arg, int fork_id)
{
	pthread_mutex_lock(&(((t_philo_arg *)arg)->global->forks[fork_id]));
	if (fetch_gamestate(((t_philo_arg *)arg)->global))
		print_msg(((t_philo_arg *)arg), "has taken a fork");
}

static void	eat(void *arg)
{
	pthread_mutex_lock(&((t_philo_arg *)arg)->deathlock);
	++((t_philo_arg *)arg)->meals;
	print_msg(((t_philo_arg *)arg), "is eating");
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
		pthread_mutex_lock(&(p->action));
		take_fork(arg, p->id);
		take_fork(arg, (p->id + 1) % p->global->nphilo);
		if (fetch_gamestate(p->global))
			eat(arg);
		pthread_mutex_unlock(&(p->global->forks[p->id]));
		pthread_mutex_unlock(&(p->global->forks[(p->id + 1)
				% p->global->nphilo]));
		pthread_mutex_unlock(&(p->action));
		if (fetch_gamestate(p->global))
			sleep_think(arg);
	}
	return (NULL);
}
