/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:16:42 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 17:53:57 by nzenzela    ###    #+. /#+    ###.fr     */
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

void			cancel_last(t_edit*edit)
{
	t_lis		*tmp;
	
	if (edit->vert == NULL)
		return ;
	tmp = edit->vert;
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
		free(edit->vert);
		edit->vert = NULL;
	}
}

void			check_event(char *mapname, t_input *in, t_edit *edit)
{
	hl_mode(in, edit);
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	if (in->key[SDL_SCANCODE_S])
	{
		if(save_map(mapname, edit))
			write(1, "\n-------Map sauver-------\n", 27);
		else
			write(1, "\n--------Map not saved-------\n", 30);
		in->key[SDL_SCANCODE_S] = SDL_FALSE;
	}
	if (in->key[SDL_SCANCODE_R])
	{
		edit->hl_sec = NULL;
		edit->nbsect = 0;
		edit->sec = 0;
		edit->hl = 0;
		edit->vert = NULL;
		edit->sect = NULL;
	}
	if (in->key[SDL_SCANCODE_Z])
	{
		cancel_last(edit);
		in->key[SDL_SCANCODE_Z] = SDL_FALSE;
	}
	if (in->mouse[SDL_BUTTON_RIGHT])
	{
		if (check_on_vec(edit, in) == 1)
			dprintf(1, "2\n");
		in->mouse[SDL_BUTTON_RIGHT] = SDL_FALSE;
	}
	if (in->mouse[SDL_BUTTON_LEFT] && in->y < HUD_BEGIN && edit->hl == 0)
	{
		edit->hud_flag = 1;
		if (edit->vert == NULL)
			edit->vert = create_vert(in->x, in->y);
		else
			add_vert(in->x, in->y, edit, edit->vert);
		in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
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
}
