/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   objenem.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/14 16:13:31 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 20:59:03 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			handle_obj(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->obj;
	while (tmp->next && tmp->text != -1)
		tmp = tmp->next;
	tmp->text = edit->input_res;
	if (tmp->next)
	{
		tmp->next->oldcol = tmp->next->col;
		tmp->next->col = tmp->col;
		tmp->col = tmp->oldcol;
	}
	else
	{
		if (edit->hl_sec->enem)
		{
			edit->hl_sec->enem->oldcol = edit->hl_sec->enem->col;
			edit->hl_sec->enem->col = BROWN;
		}
		else
			put_zer_flag(edit);
		tmp->col = tmp->oldcol;
	}
}

void			handle_enem(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->enem;
	while (tmp->next && tmp->text != -1)
		tmp = tmp->next;
	tmp->text = edit->input_res;
	if (tmp->next)
	{
		tmp->next->oldcol = tmp->next->col;
		tmp->next->col = tmp->col;
		tmp->col = tmp->oldcol;
	}
	else
	{
		put_zer_flag(edit);
		tmp->col = tmp->oldcol;
	}
}

void			draw_obj_enem(t_edit *edit)
{
	t_sec		*temp;

	if (edit->sect == NULL)
		return ;
	temp = edit->sect;
	while (temp)
	{
		if (temp->obj)
			put_vert(edit, temp->obj);
		if (temp->enem)
			put_vert(edit, temp->enem);
		temp = temp->next;
	}
}

void			obj(t_edit *edit, t_input *in)
{
	t_lis *tmp;

	if (in->key[SDL_SCANCODE_O] && edit->hl_sec)
	{
		if (edit->hl_sec->obj == NULL)
			edit->hl_sec->obj = create_vert(in->x, in->y);
		else if (edit->hl_sec->obj->text == -1)
			add_vert(in->x, in->y, edit, edit->hl_sec->obj);
		tmp = edit->hl_sec->obj;
		while (tmp->next)
			tmp = tmp->next;
		tmp->col = GREEN;
		in->key[SDL_SCANCODE_O] = SDL_FALSE;
	}
}

void			enem(t_edit *edit, t_input *in)
{
	t_lis		*tmp;

	if (in->key[SDL_SCANCODE_E] && edit->hl_sec)
	{
		if (edit->hl_sec->enem == NULL)
			edit->hl_sec->enem = create_vert(in->x, in->y);
		else if (edit->hl_sec->enem->text == -1)
			add_vert(in->x, in->y, edit, edit->hl_sec->enem);
		tmp = edit->hl_sec->enem;
		while (tmp->next)
			tmp = tmp->next;
		tmp->col = RED;
		in->key[SDL_SCANCODE_E] = SDL_FALSE;
	}
}
