/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:16:42 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 19:05:40 by nzenzela    ###    #+. /#+    ###.fr     */
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

int				click_vert(t_input *in, t_edit *edit)
{
	if (in->mouse[SDL_BUTTON_LEFT] && in->y < HUD_BEGIN && edit->hl == 0)
	{
		edit->hud_flag = 1;
		if (edit->vert == NULL)
		{
			edit->vert = create_vert(in->x, in->y);
			if (edit->vert == NULL)
				return (0);
		}
		else
		{
			if (add_vert(in->x, in->y, edit, edit->vert) == -1)
				return (0);
		}
		in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
	}
	return (1);
}

void			settings_event(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_R])
	{
		edit->nbsect = 0;
		edit->err = 0;
		edit->hud_flag = 0;
		edit->hl_sec = NULL;
		edit->hl_vert = NULL;
		edit->nbsect = 0;
		edit->sec = 0;
		edit->hl = 0;
		if (edit->vert)
			free_lis(&edit->vert);
		if (edit->player)
			free_lis(&edit->player);
		if (edit->finish)
			free_lis(&edit->finish);
		if (edit->sect)
			free_sec(&edit->sect);
	}
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
}

void			read_map(char *mapname)
{
	int		fd;
	char	magic[5];
	char	*mapfile;

	mapfile = (char*)malloc(sizeof(char) *
		(int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
	ft_strcat(ft_strcat(ft_strcat(mapfile, MAP_PATH), mapname), ".mapf");
	if ((fd = open(mapfile, O_RDONLY)) != -1)
	{
		dprintf(1, "\n------------Data Read----------\n");
		read(fd, magic, 4);
		magic[4] = '\0';
		dprintf(1, "%s\n", magic);
	}
	else
	{
		dprintf(1, "\nThe map does not exist\n");
		return ;
	}
}

int				check_event(char *mapname, t_input *in, t_edit *edit)
{
	if (in->key[SDL_SCANCODE_K] && edit->hl_sec && edit->dyn_trigger != 1)
	{
		edit->err = 2;
		in->key[SDL_SCANCODE_K] = SDL_FALSE;
	}
	print_info(edit, in);
	settings_event(edit, in);
	cancels(edit, in);
	if (click_vert(in, edit) == 0)
		return (0);
	hl_mode(in, edit);
	hl_vec(edit, in);
	if (new_vert(edit, in) == 0)
		return (0);
	portals(edit, in);
	if (check_input(edit, in) == 0)
		return (0);
	dyn_input(edit, in);
	if (enem(edit, in) == 0)
		return (0);
	if (obj(edit, in) == 0)
		return (0);
	if (create_player(edit, in) == 0)
		return (0);
	if (create_finish(edit, in) == 0)
		return (0);
	save_map(in, mapname, edit);
	if (in->key[SDL_SCANCODE_L])
	{
		in->key[SDL_SCANCODE_L] = SDL_FALSE;
		read_map(mapname);
	}
	return (1);
}
