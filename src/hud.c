/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hud.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:29:02 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 19:56:32 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			set_grid(t_edit *edit)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y % UNIT == 0 || x % UNIT == 0)
				edit->sdl.pix[y * WIN_W + x] = CYAN;
			x++;
		}
		y++;
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
		if (ft_strcmp(tmp->c_content, s2) == 0)
			tmp->trigger = 0;
		if (ft_strcmp(tmp->c_content, s1) == 0)
			tmp->trigger = 1;
		tmp = tmp->next;
	}
}

int				check_trigger(t_edit *edit, char *s)
{
	t_content	*tmp;

	tmp = edit->con;
	while (tmp)
	{
		if (ft_strcmp(tmp->c_content, s) == 0)
		{
			return (tmp->trigger);
		}
		tmp = tmp->next;
	}
	return (0);
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
	if (edit->hud_flag == 0 && check_trigger(edit, HL_SET_TUTO))
		set_tuto(edit, TUTO, HL_SET_TUTO);
	else if (edit->hud_flag == 0 && check_trigger(edit, HL_TUTO))
		set_tuto(edit, TUTO, HL_TUTO);
	else if (edit->hud_flag == 2 && !edit->hl_sec && check_trigger(edit, TUTO))
		set_tuto(edit, HL_SET_TUTO, TUTO);
	else if (edit->hud_flag == 2 && edit->hl_sec && check_trigger(edit,
				HL_SET_TUTO))
		set_tuto(edit, HL_TUTO, HL_SET_TUTO);
}
