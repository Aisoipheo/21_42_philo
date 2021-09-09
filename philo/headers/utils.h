/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:51:02 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/04 18:45:54 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int						is_num(char c);
int						my_atoi(const char *s, int *nb);
void					go_sleep(unsigned long long int ms);
unsigned long long int	get_unix_time(void);

#endif
