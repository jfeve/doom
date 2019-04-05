/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hud.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:29:02 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:57:04 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			hud(t_edit *edit)
{
	int x;
	int y;

	x = 0;
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
	x = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			edit->sdl.pix[y * WIN_W + x] = 0x656565FF;
			x++;
		}
		y++;
	}
	x = 250;
	y = 920;
	edit->sdl.pix[(y + 10) * WIN_W + x + 10] = WHITE;
	while (x < 270)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[(y + 20) * WIN_W + x] = WHITE;
		x++;
	}
	y = 920;
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
