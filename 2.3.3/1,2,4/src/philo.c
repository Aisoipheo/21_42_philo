#include "philo.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

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
		|| args->etime < 0 || args->stime < 0 || args->nphilo > SEM_VALUE_MAX)
		return (1);
	return (0);
}

static void	init(t_global *g, pid_t **pids)
{
	pid_t	ret;
	int		i;

	*pids = (pid_t *)malloc(sizeof(pid_t) * g->nphilo);
	i = g->nphilo;
	sem_unlink(PHILO_PRINTER_NAME);
	sem_unlink(PHILO_FORKPOOL_NAME);
	g->forks = sem_open(PHILO_FORKPOOL_NAME, O_CREAT, 0660, g->nphilo);
	g->printer = sem_open(PHILO_PRINTER_NAME, O_CREAT, 0660, 1);
	g->start = get_unix_time();
	while (i--)
	{
		ret = fork();
		if (ret == 0)
		{
			free(*pids);
			exit(child_proc(g, i));
		}
		(*pids)[i] = ret;
	}
}

static void	simulate(t_global *g, pid_t *pids)
{
	int		i;
	int		status;

	i = g->nphilo;
	while (i--)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
		{
			i = g->nphilo;
			while (i--)
				kill(pids[i], SIGKILL);
			break ;
		}
	}
	i = g->nphilo;
	while (i--)
		waitpid(pids[i], NULL, 0);
}

static void	destroy(t_global *g, pid_t *pids)
{
	sem_close(g->forks);
	sem_unlink(PHILO_FORKPOOL_NAME);
	sem_close(g->printer);
	sem_unlink(PHILO_PRINTER_NAME);
	free(pids);
}

int	main(int argc, char *argv[])
{
	t_global			global;
	pid_t				*pids;

	if (argc != 5 && argc != 6)
		return (1);
	if (parse_argv(&global, argc, argv))
		return (1);
	init(&global, &pids);
	simulate(&global, pids);
	destroy(&global, pids);
	return (0);
}
