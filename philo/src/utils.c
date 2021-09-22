/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:56:19 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/22 12:15:19 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

#include "utils.h"

int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int	my_atoi(const char *s, int *nb)
{
	char	sign;

	*nb = 0;
	sign = 0;
	while (s && *s && *s != '+' && *s != '-' && !is_num(*s))
		s++;
	if (*s == '-')
		sign = 1;
	if (*s == '+' || *s == '-')
		s++;
	while (s && *s && is_num(*s))
	{
		*nb = *nb * 10 + *s - '0';
		s++;
	}
	if (sign)
		*nb = -(*nb);
	return (0);
}

// 1 ms = 1000 us
void	go_sleep(unsigned long long int ms)
{
	unsigned long long int	ts;

	ts = get_unix_time();
	while (get_unix_time() - ts < ms)
		usleep(50);
}

unsigned long long int	get_unix_time(void)
{
	static struct timeval	te;

	gettimeofday(&te, NULL);
	return (te.tv_sec * 1000ULL + te.tv_usec / 1000);
}
