/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   highlight.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 04:44:01 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 21:45:59 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			clear_hl(t_edit *edit)
{
	t_sec		*tmp;
	t_lis		*temp;

	tmp = edit->sect;
	while (tmp && (tmp->vert->col == (int)WHITE || (tmp->vert->col == (int)PURPLE && tmp->vert->next->col != (int)RED)))
		tmp = tmp->next;
	if (tmp)
	{
		temp = tmp->vert;
		while (temp)
		{
			if (temp->col != (int)PURPLE)
				temp->col = WHITE;
			temp = temp->next;
		}
	}
}

void			hl_mode(t_input *in, t_edit *edit)
{	
	t_sec		*tmp;
	int			i;

	if (in->key[SDL_SCANCODE_H] && edit->sect)
	{
		in->key[SDL_SCANCODE_H] = SDL_FALSE;
		if (edit->hl == 0)
			edit->hl++;
		else if (edit->hl == 2 && edit->input_trigger != 1)
			edit->hl = 0;
		else if (edit->hl == 1)
			edit->hl--;
		if (edit->hl % 2 == 0 && edit->hl != 2)
		{
			edit->hud_flag = 0;
			edit->sec = 0;
			clear_hl_vec(edit->hl_sec);
			edit->hl_sec = NULL;
			edit->hl_vert = NULL;
			clear_hl(edit);
		}
	}
	if (edit->hl % 2 != 0 && edit->sect)
	{
		edit->hud_flag = 2;
		if (in->key[SDL_SCANCODE_RIGHT])
		{
			in->key[SDL_SCANCODE_RIGHT] = SDL_FALSE;
			clear_hl(edit);
			if (edit->sec != edit->nbsect - 1)
				edit->sec++;
			else
				edit->sec = 0;
		}
		else if (in->key[SDL_SCANCODE_LEFT])
		{
			in->key[SDL_SCANCODE_LEFT] = SDL_FALSE;
			clear_hl(edit);
			if (edit->sec != 0)
				edit->sec--;
			else
				edit->sec = edit->nbsect - 1;
		}
		i = 0;
		tmp = edit->sect;
		while (i != edit->sec)
		{
			if (tmp->next == NULL)
				tmp = edit->sect;
			else
				tmp = tmp->next;
			i++;
		}
		t_lis *temp;
		temp = tmp->vert;
		while (temp)
		{
			if (temp->col != (int)PURPLE)
			temp->col = RED;
			temp = temp->next;
		}
		if (in->key[SDL_SCANCODE_RETURN])
		{
			edit->hl = 2;
			edit->hl_sec = tmp;
		}
	}
}
