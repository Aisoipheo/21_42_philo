/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:38:18 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/10/02 12:48:59 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>

# define PHILO_GAMELOCK_NAME "/philo_gamelock"
# define PHILO_FORKPOOL_NAME "/philo_forks"
# define PHILO_PRINTER_NAME "/philo_printer"
# define PHILO_DEATHLOCK_PREFIX "/philo_deathlock_"

typedef struct s_global
{
	int								nphilo;
	int								dtime;
	int								etime;
	int								stime;
	int								neat;
	sem_t							*printer;
	sem_t							*forks;
	volatile unsigned long long int	start;
}	t_global;

typedef struct s_worker
{
	int								id;
	sem_t							*deathlock;
	sem_t							*forks;
	int								meals;
	volatile char					is_alive;
	volatile char					is_game;
	volatile unsigned long long int	last_meal;
	t_global						*global;
}	t_worker;

int		child_proc(t_global *g, int proc_id);
void	sleep_think(t_worker *w);
void	eat(t_worker *w);
void	print_msg(t_worker *w, const char *restrict msg);

#endif
