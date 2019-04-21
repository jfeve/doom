/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 16:32:55 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:06:20 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			dyn_input(t_edit *edit, t_input *in)
{
	t_content	*tmp;

	tmp = edit->con;
	while (tmp->next && tmp->display == 0)
		tmp = tmp->next;
	if (edit->dyn_trigger == 0 && tmp->display == 1)
		free_dyn_content(&edit->con);
	if (edit->dyn_trigger == 1 && tmp->display == 1)
	{
		get_title(edit, &tmp);
		if (in->key[SDL_SCANCODE_BACKSPACE])
		{
			if (tmp->cursor != 0)
			{
				tmp->cursor--;
				tmp->c_content[tmp->cursor] = '\0';
			}
			in->key[SDL_SCANCODE_BACKSPACE] = SDL_FALSE;
		}
		dyn_enter(edit, in, tmp);
		check_keyboard(in, tmp);
	}
}

void			check_input(t_edit *edit, t_input *in)
{
	t_content	*tmp;

	if (in->key[SDL_SCANCODE_T] && edit->hl_sec)
	{
		clear_hl_vec(edit->hl_sec);
		edit->hl_vert = NULL;
		in->key[SDL_SCANCODE_T] = SDL_FALSE;
		add_content(edit, "", "floor = ", init_draw(600, HUD_BEGIN + 50, 1));
		tmp = edit->con;
		while (tmp->next)
			tmp = tmp->next;
		tmp->display = 1;
		edit->dyn_trigger = 1;
	}
}
