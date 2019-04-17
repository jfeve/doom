/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hud.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:29:02 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 15:29:22 by jfeve       ###    #+. /#+    ###.fr     */
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

void			hud_hl(t_edit *edit)
{
	int			x;
	int			y;

	x = 250;
	y = 880;
	while (x < 350)
	{
		edit->sdl.pix[y * WIN_W + x] = 0xFF0000FF;
		x++;
		y++;
	}
	while (x >= 250)
	{
		edit->sdl.pix[y * WIN_W + x] = 0xFF0000FF;
		x--;
	}
	while (y > 880)
	{
		edit->sdl.pix[y * WIN_W + x] = 0xFF0000FF;
		y--;
	}
}

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
	if (edit->hud_flag == 2)
		hud_hl(edit);
}
