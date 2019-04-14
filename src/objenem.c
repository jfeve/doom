/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   objenem.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/14 16:13:31 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 16:32:53 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

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
