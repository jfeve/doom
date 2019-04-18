/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:16:42 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 18:35:10 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			update_event(t_input *in)
{
	while (SDL_PollEvent(&in->event))
	{
		if (in->event.type == SDL_QUIT)
			in->quit = SDL_TRUE;
		else if (in->event.type == SDL_KEYDOWN)
			in->key[in->event.key.keysym.scancode] = SDL_TRUE;
		else if (in->event.type == SDL_KEYUP)
			in->key[in->event.key.keysym.scancode] = SDL_FALSE;
		else if (in->event.type == SDL_MOUSEMOTION)
		{
			in->x = in->event.motion.x;
			in->y = in->event.motion.y;
			in->xrel = in->event.motion.xrel;
			in->yrel = in->event.motion.yrel;
		}
		else if (in->event.type == SDL_MOUSEWHEEL)
		{
			in->xwheel = in->event.wheel.x;
			in->ywheel = in->event.wheel.y;
		}
		else if (in->event.type == SDL_MOUSEBUTTONDOWN)
			in->mouse[in->event.button.button] = SDL_TRUE;
		else if (in->event.type == SDL_MOUSEBUTTONUP)
			in->mouse[in->event.button.button] = SDL_FALSE;
	}
}

void			switch_highlight(t_input *in, t_edit *edit)
{
	if (in->mouse[SDL_BUTTON_LEFT] && in->y < HUD_BEGIN && edit->hl == 0)
	{
		edit->hud_flag = 1;
		if (edit->vert == NULL)
			edit->vert = create_vert(in->x, in->y);
		else
			add_vert(in->x, in->y, edit, edit->vert);
		in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
	}
}

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

void			settings_event(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_R])
	{
		edit->nbsect = 0;
		edit->err = 0;
		edit->hud_flag = 0;
		edit->hl_sec = NULL;
		edit->nbsect = 0;
		edit->sec = 0;
		edit->hl = 0;
		edit->vert = NULL;
		edit->sect = NULL;
	}
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
}

void			check_event(char *mapname, t_input *in, t_edit *edit)
{
	if (in->key[SDL_SCANCODE_D])
	{
		add_content(edit, "testcontent ", "testtitle  ", init_draw(WIN_W / 2, WIN_H / 2, 1));
		in->key[SDL_SCANCODE_D] = SDL_FALSE;
	}
	if (in->key[SDL_SCANCODE_X])
	{
		add_content(edit, "tesqwdqdwtent ", "tqwdtle  ", init_draw(WIN_W / 3, WIN_H / 2, 1));
		in->key[SDL_SCANCODE_X] = SDL_FALSE;
	}
	print_info(edit, in);
	settings_event(edit, in);
	cancels(edit, in);
	switch_highlight(in, edit);
	hl_mode(in, edit);
	hl_vec(edit, in);
	new_vert(edit, in);
	portals(edit, in);
	check_input(edit, in);
	// input_mode(in, edit);
	enem(edit, in);
	obj(edit, in);
	create_player(edit, in);
	save_map(in, mapname, edit);
}
