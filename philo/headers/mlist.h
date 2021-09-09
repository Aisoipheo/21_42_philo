/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:16:36 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/04 16:37:55 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLIST_H
# define MLIST_H

typedef struct s_mlist_elem
{
	void				*ptr;
	struct s_mlist_elem	*next;
}			t_mlist_elem;

typedef struct s_mlist
{
	t_mlist_elem		*head;
	t_mlist_elem		*tail;
}			t_mlist;

t_mlist		*new_mlist(void);
int			mlist_new(t_mlist *self, void *ptr);
void		mlist_free(t_mlist *self, void *ptr);
void		mlist_destroy(t_mlist *self);

#endif
