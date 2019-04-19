/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hud.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:29:02 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 18:19:53 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			hud_vert(t_edit *edit)
{
	int			x;
	int			y;

	x = 250;
	y = 920;
	edit->sdl.pix[(y + 10) * WIN_W + x + 10] = WHITE;
	while (x < 270)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[(y + 20) * WIN_W + x] = WHITE;
		x++;
	}
	while (y < 940)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[y * WIN_W + x - 20] = WHITE;
		y++;
	}
	x = 260;
	y = 930;
	while (x < 450)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		x++;
	}
}

void			grey_hud(t_edit *edit)
{
	int			x;
	int			y;

	y = HUD_BEGIN + 10;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			edit->sdl.pix[y * WIN_W + x] = 0x626965FF;
			x++;
		}
		y++;
	}
}

void			set_tuto(t_edit *edit, char *s1, char *s2)
{
	t_content	*tmp;

	tmp = edit->con;
	while (tmp)
	{
		if (ft_strcmp(tmp->c_title, s2) == 0)
			tmp->trigger = 0;
		tmp = tmp->next;
	}
	tmp = edit->con;
	while (tmp && ft_strcmp(tmp->c_title, s1) != 0)
		tmp = tmp->next;
	tmp->trigger = 1;
}

void			hud(t_edit *edit)
{
	int x;
	int y;

	y = HUD_BEGIN;
	while (y < HUD_BEGIN + 10)
	{
		x = 0;
		while (x < WIN_W)
		{
			edit->sdl.pix[y * WIN_W + x] = 0x000000FF;
			x++;
		}
		y++;
	}
	grey_hud(edit);
	if (edit->hud_flag == 1)
		hud_vert(edit);
	else if (edit->hud_flag == 2)
		hud_hl(edit);
	else
		set_tuto(edit, TUTO, HL_SET_TUTO);
}
