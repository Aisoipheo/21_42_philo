/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:16:05 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/09 11:03:18 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlist.h"
#include "philo.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

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

static void	simulate(t_args *args)
{
	printf("nphilo: %d\n", args->nphilo);
	printf("dtime: %d\n", args->dtime);
	printf("etime: %d\n", args->etime);
	printf("stime: %d\n", args->stime);
	printf("neat: %d\n", args->neat);
}

int	main(int argc, char *argv[])
{
	t_args	args;

	if (argc != 5 && argc != 6)
		return (1);
	go_sleep(1000);
	parse_argv(&args, argc, argv);
	simulate(&args);
	return (0);
}
