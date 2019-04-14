/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:16:42 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 14:03:47 by jfeve       ###    #+. /#+    ###.fr     */
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

void			cancel_last(t_lis **vert)
{
	t_lis		*tmp;
	
	if (*vert == NULL)
		return ;
	tmp = *vert;
	if (tmp->next)
		while(tmp->next->next)
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

void			place_enemy(t_input *in, t_edit *edit)
{
	t_lis	*tmp;

	if (in->key[SDL_SCANCODE_E] && edit->hl_sec)
	{

		if (edit->hl_sec->enem == NULL)
			edit->hl_sec->enem = create_vert(in->x, in->y);
		else
			add_vert(in->x, in->y, edit, edit->hl_sec->enem);
		tmp = edit->hl_sec->enem;
		while (tmp->next)
			tmp = tmp->next;
		tmp->col = RED;
		in->key[SDL_SCANCODE_E] = SDL_FALSE;
	}
}

void			check_event(char *mapname, t_input *in, t_edit *edit)
{
	draw_text(edit);
	input_mode(in, edit);
	hl_mode(in, edit);
	portals(edit, in);
	save_map(in, mapname, edit);
	if (in->key[SDL_SCANCODE_G])
	{
		print_sec(edit->sect);
		in->key[SDL_SCANCODE_G] = SDL_FALSE;
	}
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	if (in->key[SDL_SCANCODE_T] && edit->hl_sec)
	{
		if (edit->hl_vert)
		{
			if (edit->hl_vert->next)
				edit->hl_vert->next->col = edit->hl_vert->next->oldcol;
			else
				edit->hl_sec->vert->col = edit->hl_sec->vert->oldcol;
		}
		edit->hl_vert = NULL;
		edit->input_flag = 1;
		edit->input_trigger = 1;
		in->key[SDL_SCANCODE_T] = SDL_FALSE;
	}
	if (in->key[SDL_SCANCODE_R])
	{
		edit->input_flag = 0;
		edit->input_trigger = 0;
		edit->input_cursor = 0;
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
	if (in->key[SDL_SCANCODE_A] && edit->hl_vert && edit->hl_sec->floor == -1)
	{
		t_lis *tmp;

		tmp = edit->hl_sec->vert;
		while (tmp)
		{
			if (parse_data(in->x, in->y, edit, tmp) == 0)
				break ;
			tmp = tmp->next;
		}
		if (!tmp)
			put_new_vert(edit, in);
		else
			edit->oldvert = NULL;
		in->key[SDL_SCANCODE_A] = SDL_FALSE;
	}
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
	if (in->key[SDL_SCANCODE_O] && edit->hl_sec)
	{
		if (edit->hl_sec->obj == NULL)
			edit->hl_sec->obj = create_vert(in->x, in->y);
		else
			add_vert(in->x, in->y, edit, edit->hl_sec->obj);
		t_lis *tmp;

		tmp = edit->hl_sec->obj;
		while (tmp->next)
			tmp = tmp->next;
		tmp->col = GREEN;
		in->key[SDL_SCANCODE_O] = SDL_FALSE;
	}
	if (in->key[SDL_SCANCODE_E] && edit->hl_sec)
	{
		if (edit->hl_sec->enem == NULL)
			edit->hl_sec->enem = create_vert(in->x, in->y);
		else
			add_vert(in->x, in->y, edit, edit->hl_sec->enem);
		t_lis *tmp;

		tmp = edit->hl_sec->enem;
		while (tmp->next)
			tmp = tmp->next;
		tmp->col = RED;
		in->key[SDL_SCANCODE_E] = SDL_FALSE;
	}
	switch_highlight(in, edit);
	place_enemy(in, edit);
}
