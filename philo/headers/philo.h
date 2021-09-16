/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:38:18 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/16 17:15:39 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t		*lock;
	int					state;
}	t_fork;

typedef struct s_global
{
	int						nphilo;
	int						dtime;
	int						etime;
	int						stime;
	int						neat;
	unsigned long long int	start;
	volatile int			gamestate;
	pthread_mutex_t			*gamelock;
	pthread_mutex_t			*printer;
	int						ready;
}	t_global;

typedef struct s_philo_arg
{
	int						id;
	unsigned long long int	last_meal;
	int						meals;
	t_global				*global;
}	t_philo_arg;

void	print_msg(t_global *global, int id, const char *restrict msg);
void	*philo_job(void *arg);
int		fetch_gamestate(t_global *global);
void	set_gamestate(t_global *global, int newval);

#endif
