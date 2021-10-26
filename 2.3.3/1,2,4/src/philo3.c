#include "philo.h"
#include "utils.h"

#include <stdio.h>

void	print_msg(t_worker *w, const char *restrict msg)
{
	sem_wait(w->global->printer);
	printf("%llu %d %s\n", get_unix_time() - w->global->start, w->id + 1, msg);
	sem_post(w->global->printer);
}

void	sleep_think(t_worker *w)
{
	if (w->is_game)
		print_msg(w, "is sleeping");
	go_sleep(w->global->stime);
	if (w->is_game)
		print_msg(w, "is thinking");
}

void	eat(t_worker *w)
{
	sem_wait(w->deathlock);
	w->last_meal = get_unix_time();
	++w->meals;
	sem_post(w->deathlock);
	if (w->is_game)
		print_msg(w, "is eating");
	go_sleep(w->global->etime);
}
