/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   portals.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/14 16:41:55 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 17:16:53 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				check_neigh_2(t_lis **vert, t_lis **next, t_lis **tmp, t_sec
		**temp)
{
	if ((*tmp)->x == (*vert)->x && (*tmp)->y == (*vert)->y && (*temp)->vert->x
		== (*next)->x && (*temp)->vert->y == (*next)->y)
	{
		(*tmp)->port = 1;
		(*temp)->vert->col = PURPLE;
		(*vert)->neigh = (*temp)->id;
		return (1);
	}
	else if ((*tmp)->x == (*next)->x && (*tmp)->y == (*next)->y &&
		(*temp)->vert->x == (*vert)->x && (*temp)->vert->y == (*vert)->y)
	{
		(*temp)->vert->col = PURPLE;
		(*tmp)->port = 1;
		(*vert)->neigh = (*temp)->id;
		return (1);
	}
	return (0);
}

int				check_neigh_1(t_lis **vert, t_lis **next, t_lis **tmp,
		t_edit *edit)
{
	if ((*tmp)->x == (*vert)->x && (*tmp)->y == (*vert)->y
		&& (*tmp)->next->x == (*next)->x && (*tmp)->next->y == (*next)->y)
	{
		(*tmp)->port = 1;
		(*tmp)->col = PURPLE;
		(*tmp)->neigh = edit->hl_sec->id;
		return (1);
	}
	else if ((*tmp)->x == (*next)->x && (*tmp)->y == (*next)->y &&
		(*tmp)->next->x == (*vert)->x && (*tmp)->next->y == (*vert)->y)
	{
		(*tmp)->port = 1;
		(*tmp)->next->col = PURPLE;
		(*tmp)->neigh = edit->hl_sec->id;
		return (1);
	}
	return (0);
}

int				get_neighbor(t_edit *edit, t_lis **vert, t_lis **next)
{
	t_lis		*tmp;
	t_sec		*temp;

	temp = edit->sect;
	while (temp)
	{
		tmp = temp->vert;
		while (tmp->next && temp != edit->hl_sec)
		{
			if (check_neigh_1(vert, next, &tmp, edit) == 1)
			{
				(*vert)->neigh = temp->id;
				return (1);
			}
			tmp = tmp->next;
		}
		if (temp != edit->hl_sec)
			if (check_neigh_2(vert, next, &tmp, &temp) == 1)
			{
				tmp->neigh = edit->hl_sec->id;
				return (1);
			}
		temp = temp->next;
	}
	return (0);
}

void			portals(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_P] && edit->hl_vert)
	{
		if (edit->hl_vert->next)
		{
			if (get_neighbor(edit, &edit->hl_vert, &edit->hl_vert->next))
			{
				edit->hl_vert->port = 1;
				edit->hl_vert->next->col = PURPLE;
				edit->hl_vert = NULL;
			}
		}
		else
		{
			if (get_neighbor(edit, &edit->hl_vert, &edit->hl_sec->vert))
			{
				edit->hl_vert->port = 1;
				edit->hl_sec->vert->col = PURPLE;
				edit->hl_vert = NULL;
			}
		}
	}
}
