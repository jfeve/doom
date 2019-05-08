/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_draw.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 14:03:40 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 12:48:07 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Draws a line from point a to point b
*/

static void	bresenham(t_sdl *sdl, t_point a, t_point b, int color)
{
	t_line	l;

	l.dx = (int)fabs((double)(b.x - a.x));
	l.dy = (int)fabs((double)(b.y - a.y));
	l.sx = (a.x < b.x) ? 1 : -1;
	l.sy = (a.y < b.y) ? 1 : -1;
	l.err = ((l.dx > l.dy) ? l.dx : -l.dy) / 2;
	while (1)
	{
		sdl->pix[a.y * RWIN_W + a.x] = color;
		if (a.x == b.x && a.y == b.y)
			break ;
		l.err2 = l.err;
		if (l.err2 > -l.dx)
		{
			l.err -= l.dy;
			a.x += l.sx;
		}
		if (l.err2 < l.dy)
		{
			l.err += l.dx;
			a.y += l.sy;
		}
	}
}

/*
** Draws the aiming cross in the middle of the screen
*/

static void	draw_cross(t_sdl *sdl)
{
	bresenham(sdl, (t_point){RWIN_W / 2 - 25, RWIN_H / 2},
	(t_point){RWIN_W / 2 - 10, RWIN_H / 2}, 0x000000ff);
	bresenham(sdl, (t_point){RWIN_W / 2 + 25, RWIN_H / 2},
	(t_point){RWIN_W / 2 + 10, RWIN_H / 2}, 0x000000ff);
	bresenham(sdl, (t_point){RWIN_W / 2, RWIN_H / 2 + 25},
	(t_point){RWIN_W / 2, RWIN_H / 2 + 10}, 0x000000ff);
	bresenham(sdl, (t_point){RWIN_W / 2, RWIN_H / 2 - 25},
	(t_point){RWIN_W / 2, RWIN_H / 2 - 10}, 0x000000ff);
}

/*
** Draws the entire hud (gun, life, ammo)
*/

static void	draw_main_hud(t_sdl *sdl, t_hud *hud)
{
	draw_sprite(sdl, hud->gun[hud->id], 2 * RWIN_W / 3,
	RWIN_H - hud->gun[hud->id]->h);
	draw_sprite(sdl, hud->ammoicon, 10, RWIN_H - hud->ammoicon->h - 10);
	draw_sprite(sdl, hud->lifeicon, 10, RWIN_H - hud->ammoicon->h -
	hud->lifeicon->h - 20);
	draw_sprite(sdl, hud->nblife, 20 + hud->lifeicon->w, RWIN_H -
	hud->ammoicon->h - (hud->lifeicon->h / 2) - 35);
	draw_sprite(sdl, hud->nbammo, 20 + hud->ammoicon->w, RWIN_H -
	(hud->ammoicon->h / 2) - 25);
	if (hud->timer > 0)
	{
		draw_sprite(sdl, hud->text, RWIN_W / 2 - 40, RWIN_H / 2 - 12);
		if (hud->timer == 1 && hud->text)
		{
			SDL_FreeSurface(hud->text);
			hud->text = NULL;
		}
		hud->timer--;
	}
	else if (hud->timer < -1)
	{
		hud->timer++;
		draw_sprite(sdl, hud->text, RWIN_W / 2 - 70, RWIN_H / 2 - 12);
	}
}

void		draw_hud(t_sdl *sdl, t_hud *hud, int ammo)
{
	if (hud->anim == SDL_FALSE)
		hud->id = 0;
	else
		hud->id++;
	if (hud->id > 5)
	{
		hud->anim = SDL_FALSE;
		hud->id = 0;
	}
	if (hud->anim == SDL_FALSE && hud->id == 0 && ammo == 0)
		hud->id = 6;
	draw_main_hud(sdl, hud);
	if (hud->has_key)
		draw_sprite(sdl, hud->items[0], 10, 10);
	if (hud->has_armor)
		draw_sprite(sdl, hud->items[1], 20 + hud->items[0]->w, 10);
	draw_cross(sdl);
}
