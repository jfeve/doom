/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:08:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 05:41:02 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				usage(void)
{
	ft_putendl("Usage : ./doom-nukem <file>");
	ft_putendl("\tor ./doom-nukem edit <mapname>.");
	return (0);
}

int				init_content(t_edit *edit)
{
	edit->con = create_content();
	if (edit->con == NULL)
		return (0);
	edit->con->x = WIN_W / 3;
	edit->con->y = 35;
	edit->con->display = 0;
	edit->con->cursor = 0;
	edit->con->trigger = 1;
	fill_str_content(256, edit->con->c_title, "level editor ");
	fill_str_content(2048, edit->con->c_content, "v1");
	return (1);
}

int				choose_set(t_edit*edit)
{
	if (edit->hl_sec_temp)
	{
		if (edit->hl_sec_temp->floor == -1)
			return (1);
	}
	else if (edit->hl_sec)
		if (edit->hl_sec->floor == -1)
			return (1);
	return (0);
}

void			set_trigger(t_edit *edit, int choice, int trig)
{
	t_content	*tmp;
	char		*str;
	char		*title;

	tmp = edit->con;
	title = ft_strdup("\0");
	if (choice == 0)
		str = ft_strdup("set");
	else
		str = ft_strdup("not set");
	while (tmp)
	{
		if ((ft_strcmp(title, tmp->c_title) == 0) &&
				(ft_strcmp(str, tmp->c_content) == 0))
		{
			tmp->trigger = trig;
			return ;
		}
		tmp = tmp->next;
	}
}

void			draw_wf(int x, int y, t_edit *edit)
{
	int			i;
	int			j;

	i = x;
	j = y;
//	if (!edit->time.oldtime)
//		edit->time.oldtime = SDL_GetTicks();
//	else
//	{
//		edit->time.time = SDL_GetTicks();
//		if (edit->time.time > edit->time.oldtime + 2000)
//		{
//			set_trigger(edit, choose_set(edit), 0);
//			edit->time.oldtime = 0;
//			edit->err = 0;
//			return ;
//		}
//	}
	if (edit->dyn_trigger == 1)
	{
		set_trigger(edit, choose_set(edit), 0);
		return ;
	}
	while (j < y + WF_H)
	{
		i = x;
		while (i < x + WF_W)
		{
			if (i < x + 10 || i > x + WF_W - 10)
				edit->sdl.pix[i + j * WIN_W] = WHITE;
			else if (j < y + 10 || j > y + WF_H - 10)
				edit->sdl.pix[i + j * WIN_W] = WHITE;
			else
				edit->sdl.pix[i + j * WIN_W] = WF_COL;
			i++;
		}
		j++;
	}
	set_trigger(edit, choose_set(edit), 1);
}

void			draw_back(t_edit *edit)
{
	int			i;
	int			j;

	j = HUD_BEGIN + 37;
	while (j < HUD_BEGIN + 87)
	{
		i = 575;
		while (i < 850)
		{
			edit->sdl.pix[j * WIN_W + i] = BROWN;
			i++;
		}
		j++;
	}
}

int				get_update(t_edit *edit, t_input *in, char *mapname)
{
	clear_tab(&edit->sdl);
	update_event(in);
	if (check_event(mapname, in, edit) == 0)
		return (0);
	set_grid(edit);
	hud(edit);
	put_vert(edit, edit->vert);
	draw_obj_enem(edit);
	draw_vec(edit, *in);
	draw_sec(edit);
	if (edit->player)
		draw_vert(edit->player, edit);
	if (edit->finish)
		draw_vert(edit->finish, edit);
	if (edit->hl_sec_temp || edit->hl_sec)
		draw_wf(WIN_W - WF_W, WIN_H - WF_H, edit);
	if (edit->dyn_trigger == 1)
		draw_back(edit);
	prepare_draw(edit);
	return (1);
}

void			render(void)
{
	return ;
}

int				main(int argc, char **argv)
{
	if (argc == 3 && ft_strcmp(argv[1], "edit") == 0)
		level_editor(argv[2]);
	else if (argc == 2 && ft_strcmp(argv[1], "game") == 0)
		render();
	else
		return (usage());
	return (0);
}
