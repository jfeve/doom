/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   editor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 18:18:31 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 18:13:10 by nzenzela    ###    #+. /#+    ###.fr     */
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
	{
		free_all(2, &edit);
		return (ft_putendl("Map name not valid"));
	}
	while (!in.quit)
	{
		if (get_update(&edit, &in, mapname) == 0)
		{
			free_all(2, &edit);
			return ;
		}
		if (display_frame(edit.sdl.ren, edit.sdl.pix) == 0)
		{
			free_all(2, &edit);
			return ;
		}
		SDL_Delay(1000 / 60);
	}
	free_all(2, &edit);
	return ;
}

int				free_content(t_edit *edit)
{
	t_content	*curr;
	t_content	*tmp;

	curr = edit->con;
	while (curr != NULL)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	edit->con = NULL;
	return (0);
}

int				basic_contents(t_edit *edit)
{
	if (add_content(edit, TUTO, "create : \n", init_draw(10, 930, 1)) == 0)
		return (free_content(edit));
	if (add_content(edit, HL_SET_TUTO, "explore : \n",
					init_draw(10, 930, 0)) == 0)
		return (free_content(edit));
	if (add_content(edit, HL_TUTO, "highlight : \n",
					init_draw(10, 930, 0)) == 0)
		return (free_content(edit));
	if (add_content(edit, "set", NULL, init_draw(WIN_W - WF_W + 75, WIN_H - (WF_H / 2) - 15, 0)) == 0)
		return (free_content(edit));
	if (add_content(edit, "not set", NULL, init_draw(WIN_W - WF_W + 40, WIN_H - (WF_H / 2) - 15, 0)) == 0)
		return (free_content(edit));
	return (1);
}

int				init_edit(t_edit *edit)
{
	if (init_content(edit) == 0)
		return (0);
	if (basic_contents(edit) == 0)
		return (0);
	if (sdl_init(&edit->sdl) == 0)
		return (free_content(edit));
	edit->time.oldtime = 0;
	edit->player = NULL;
	edit->finish = NULL;
	edit->dyn_trigger = 0;
	edit->hl_sec = NULL;
	edit->hl_vert = NULL;
	edit->nbsect = 0;
	edit->hl = 0;
	edit->sect = 0;
	edit->err = 0;
	edit->vert = NULL;
	edit->sect = NULL;
	return (1);
}
