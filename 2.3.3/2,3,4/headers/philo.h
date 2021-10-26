#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_global
{
	int								nphilo;
	int								dtime;
	int								etime;
	int								stime;
	int								neat;
	volatile unsigned long long int	start;
	volatile int					gamestate;
	pthread_mutex_t					gamelock;
	pthread_mutex_t					printer;
	pthread_mutex_t					*forks;
	volatile int					ready;
}	t_global;

typedef struct s_philo_arg
{
	int								id;
	volatile unsigned long long int	last_meal;
	int								meals;
	t_global						*global;
	pthread_mutex_t					action;
	pthread_mutex_t					deathlock;
}	t_philo_arg;

void	print_msg(t_philo_arg *arg, const char *restrict msg);
void	*philo_job(void *arg);
void	*waiter_job(void *arg);
int		fetch_gamestate(t_global *global);
void	set_gamestate(t_global *global, int newval);

#endif
