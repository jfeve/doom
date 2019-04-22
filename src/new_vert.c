/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_vert.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 13:40:20 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 22:47:06 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			swap_datas(t_lis *vert, t_lis *last)
{
	t_lis tmp;

	if (!vert)
		return ;
	while (vert != last)
	{
		tmp.x = vert->x;
		tmp.y = vert->y;
		tmp.col = vert->col;
		tmp.neigh = vert->neigh;
		tmp.port = vert->port;
		vert->x = last->x;
		vert->y = last->y;
		vert->col = last->col;
		vert->port = last->port;
		vert->neigh = last->neigh;
		last->x = tmp.x;
		last->y = tmp.y;
		last->col = tmp.col;
		last->neigh = tmp.neigh;
		last->port = tmp.port;
		vert = vert->next;
	}
}

int				put_new_vert(t_edit *edit, t_input *in)
{
	t_lis		*tmp;
	t_lis		*last;

	if (add_vert(in->x, in->y, edit, edit->hl_sec->vert) == -1)
		return (0);
	last = edit->hl_sec->vert;
	while (last->next)
		last = last->next;
	last->col = RED;
	if (edit->hl_vert->next != last && edit->hl_vert->next)
		tmp = edit->hl_vert->next;
	else
		tmp = edit->hl_sec->vert;
	swap_datas(tmp, last);
	tmp->col = RED;
	if (tmp->next)
		tmp->next->col = GREEN;
	else
		edit->hl_sec->vert->col = GREEN;
	edit->hl_vert = tmp;
	return (1);
}

int				new_vert(t_edit *edit, t_input *in)
{
	t_lis		*tmp;

	if (in->key[SDL_SCANCODE_A] && edit->hl_vert && edit->hl_sec->floor == -1 &&
			in->y < HUD_BEGIN)
	{
		tmp = edit->hl_sec->vert;
		while (tmp)
		{
			if (parse_data(in->x, in->y, edit, tmp) == 0)
				break ;
			tmp = tmp->next;
		}
		if (!tmp)
		{
			if (put_new_vert(edit, in) == 0)
				return (0);
		}
		else
			edit->oldvert = NULL;
		in->key[SDL_SCANCODE_A] = SDL_FALSE;
	}
	return (1);
}
