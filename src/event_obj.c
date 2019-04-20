/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event_obj.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 14:50:45 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 14:50:53 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			create_player(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_J] && edit->hl_sec)
	{
		in->key[SDL_SCANCODE_J] = SDL_FALSE;
		if (!edit->player)
		{
			edit->player = create_vert(in->x, in->y);
			edit->player->col = SKYBLUE;
			edit->player->text = edit->hl_sec->id;
		}
		else if (edit->player->x != arr(in->x) && edit->player->y != arr(in->y))
		{
			free(edit->player);
			edit->player = create_vert(in->x, in->y);
			edit->player->col = SKYBLUE;
			edit->player->text = edit->hl_sec->id;
		}
	}
}

void			create_finish(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_F] && edit->hl_sec)
	{
		in->key[SDL_SCANCODE_F] = SDL_FALSE;
		if (!edit->finish)
		{
			edit->finish = create_vert(in->x, in->y);
			edit->finish->col = YELLOW;
			edit->finish->text = edit->hl_sec->id;
		}
		else if (edit->finish->x != arr(in->x) && edit->finish->y != arr(in->y))
		{
			free(edit->finish);
			edit->finish = create_vert(in->x, in->y);
			edit->finish->col = YELLOW;
			edit->finish->text = edit->hl_sec->id;
		}
	}
}