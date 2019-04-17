/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 15:03:25 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 15:24:41 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			cancel_last(t_lis **vert)
{
	t_lis		*tmp;

	if (*vert == NULL)
		return ;
	tmp = *vert;
	if (tmp->next)
		while (tmp->next->next)
			tmp = tmp->next;
	if (tmp->next)
	{
		free(tmp->next);
		tmp->next = NULL;
	}
	else
	{
		free(*vert);
		*vert = NULL;
	}
}

void			clear_hl_vec(t_sec *sec)
{
	t_lis		*tmp;

	if (sec == NULL)
		return ;
	tmp = sec->vert;
	while (tmp)
	{
		if (tmp->col == (int)GREEN)
			tmp->col = tmp->oldcol;
		tmp = tmp->next;
	}
}

void			cancels(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_Z])
	{
		if (edit->vert)
			cancel_last(&edit->vert);
		else if (edit->hl_sec)
			if (edit->hl_sec->obj)
				cancel_last(&edit->hl_sec->obj);
		in->key[SDL_SCANCODE_Z] = SDL_FALSE;
	}
	if (in->key[SDL_SCANCODE_X])
	{
		if (edit->hl_sec)
			if (edit->hl_sec->enem)
				cancel_last(&edit->hl_sec->enem);
	}
}
