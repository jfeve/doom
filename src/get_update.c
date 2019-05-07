/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_update.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 20:24:06 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 21:10:07 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	draw_wf(int x, int y, t_edit *edit)
{
	int			i;
	int			j;

	j = y;
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

static void	draw_back(t_edit *edit)
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

static void	draw_obj_enem(t_edit *edit)
{
	t_sec		*temp;

	if (edit->sect == NULL)
		return ;
	temp = edit->sect;
	while (temp)
	{
		if (temp->obj)
			put_vert(edit, temp->obj);
		if (temp->enem)
			put_vert(edit, temp->enem);
		temp = temp->next;
	}
}

int			get_update(t_edit *edit, t_input *in, char *mapname)
{
	clear_tab(&edit->sdl, WIN_W, WIN_H);
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

void		handle_enem(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->enem;
	while (tmp->next && tmp->text != -1)
		tmp = tmp->next;
	if (edit->input_res > 4)
		return ;
	tmp->text = edit->input_res;
	if (tmp->next)
	{
		tmp->next->oldcol = tmp->next->col;
		tmp->next->col = tmp->col;
		tmp->col = tmp->oldcol;
	}
	else
	{
		edit->dyn_trigger = 0;
		tmp->col = tmp->oldcol;
	}
}
