/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   editor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 18:18:31 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 11:05:36 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			free_lis(t_lis **vert)
{
	t_lis		*curr;
	t_lis		*tmp;

	curr = *vert;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*vert = NULL;
}

void			free_sec(t_sec **sec)
{
	t_sec		*curr;
	t_sec		*tmp;

	curr = *sec;
	while (curr)
	{
		tmp = curr->next;
		if (curr->vert)
			free_lis(&curr->vert);
		if (curr->obj)
			free_lis(&curr->obj);
		if (curr->enem)
			free_lis(&curr->enem);
		free(curr);
		curr = tmp;
	}
	*sec = NULL;
}

void			free_all(int flag, t_edit *edit)
{
	if (flag >= 1)
		free_content(edit);
	if (flag >= 2)
		free_sdl(&edit->sdl, 6);
	if (edit->vert)
		free_lis(&edit->vert);
	if (edit->sect)
		free_sec(&edit->sect);
	if (edit->player)
		free_lis(&edit->player);
	if (edit->finish)
		free_lis(&edit->finish);
	edit->hl_sec = NULL;
	edit->hl_vert = NULL;
	edit->oldvert = NULL;
	edit->hl_sec_temp = NULL;
}

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

int				init_edit(t_edit *edit)
{
	if (init_content(edit) == 0)
		return (0);
	if (add_content(edit, TUTO, "create : \n", init_draw(10, 930, 1)) == 0)
		return (free_content(edit));
	if (add_content(edit, HL_SET_TUTO, "explore : \n", init_draw(10, 930, 0)) == 0)
		return (free_content(edit));
	if (add_content(edit, HL_TUTO, "highlight : \n", init_draw(10, 930, 0)) == 0)
		return (free_content(edit));
	if (sdl_init(&edit->sdl) == 0)
		return (free_content(edit));
	fill_wf(edit);
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
