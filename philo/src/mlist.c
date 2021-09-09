/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:19:46 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/09/04 17:44:39 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlist.h"

static t_mlist_elem	*new_mlist_elem__(void *ptr)
{
	t_mlist_elem	*p;

	p = (t_mlist_elem *)malloc(sizeof(t_mlist_elem));
	if (p)
	{
		p->ptr = ptr;
		p->next = NULL;
	}
	return (p);
}

// returns NULL if allocation failed
t_mlist	*new_mlist(void)
{
	t_mlist	*mlist;

	mlist = (t_mlist *)malloc(sizeof(t_mlist));
	if (mlist)
	{
		mlist->head = NULL;
		mlist->tail = NULL;
	}
	return (mlist);
}

// returns 1 if allocation failed
int	mlist_new(t_mlist *self, void *ptr)
{
	if (self)
	{
		if (NULL == self->head)
		{
			self->head = new_mlist_elem__(ptr);
			if (NULL == self->head)
				return (1);
			self->tail = self->head;
		}
		else
		{
			self->tail->next = new_mlist_elem__(ptr);
			if (NULL == self->tail->next)
				return (1);
			self->tail = self->tail->next;
		}
		return (0);
	}
	return (1);
}

void	mlist_free(t_mlist *self, void *ptr)
{
	t_mlist_elem	*p;
	t_mlist_elem	*prev;

	if (!self)
		return ;
	p = self->head;
	while (p && p->ptr != ptr)
	{
		prev = p;
		p = p->next;
	}
	if (!p)
		return ;
	if (p == self->head && p == self->tail)
		self->head = NULL;
	if (p == self->head && p == self->tail)
		self->tail = NULL;
	if (p == self->head && p != self->tail)
		self->head = p->next;
	if (p != self->head && p == self->tail)
		self->tail = prev;
	if (prev)
		prev->next = p->next;
	free(p->ptr);
	free(p);
}

void	mlist_destroy(t_mlist *self)
{
	if (self)
	{
		while (self->head)
		{
			self->tail = self->head->next;
			free(self->head->ptr);
			free(self->head);
			self->head = self->tail;
		}
		free(self);
	}
}
