/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hl_vec.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/14 16:43:02 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 16:49:20 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			hl_vec_color(t_edit *edit, t_lis **tmp)
{
	if ((*tmp)->next)
	{
		(*tmp)->next->oldcol = (*tmp)->next->col;
		(*tmp)->next->col = GREEN;
		edit->hl_vert = *tmp;
	}
	else
	{
		edit->hl_sec->vert->oldcol = edit->hl_sec->vert->col;
		edit->hl_sec->vert->col = GREEN;
		edit->hl_vert = *tmp;
	}
}

void			hl_vec(t_edit *edit, t_input *in)
{
	int			v;
	t_lis		*tmp;
	t_point		point;

	if (in->mouse[SDL_BUTTON_RIGHT] && edit->hl_sec && edit->input_trigger != 1)
	{
		point.x = in->x;
		point.y = in->y;
		if ((v = check_on_vec(&point, edit->hl_sec)) != 0)
		{
			clear_hl_vec(edit->hl_sec);
			tmp = edit->hl_sec->vert;
			while (v > 1 && tmp)
			{
				tmp = tmp->next;
				v--;
			}
			hl_vec_color(edit, &tmp);
		}
		in->mouse[SDL_BUTTON_RIGHT] = SDL_FALSE;
	}
}
