/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   editor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 18:18:31 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 19:51:32 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			level_editor(char *mapname)
{
	t_edit		edit;
	t_input		in;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&edit, sizeof(t_edit));
	if (init_edit(&edit) == 0)
		return (ft_putendl("Init Edit Error"));
	if (!check_mapname(mapname))
		return (ft_putendl("Map name not valid"));
	while (!in.quit)
	{
		get_update(&edit, &in, mapname);
		if (display_frame(edit.sdl.ren, edit.sdl.pix) == 0)
		{
			free_sdl(&edit.sdl, 5);
			return ;
		}
		SDL_Delay(1000 / 60);
	}
	return ;
}

int				init_edit(t_edit *edit)
{
	init_content(edit);
	add_content(edit, TUTO, "create : \n", init_draw(10, 930, 1));
	add_content(edit, HL_SET_TUTO, "explore : \n", init_draw(10, 930, 0));
	add_content(edit, HL_TUTO, "highlight : \n", init_draw(10, 930, 0));
	edit->player = NULL;
	edit->finish = NULL;
	edit->dyn_trigger = 0;
	edit->hl_sec = NULL;
	edit->hl_vert = NULL;
	edit->nbsect = 0;
	edit->hl = 0;
	edit->sect = 0;
	if (sdl_init(&edit->sdl) == 0)
		return (0);
	edit->err = 0;
	edit->vert = NULL;
	edit->sect = NULL;
	return (1);
}
