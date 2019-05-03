/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_draw.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 14:03:40 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 13:41:26 by flombard    ###    #+. /#+    ###.fr     */
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
		sdl->pix[a.y * WIN_W + a.x] = color;
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
	bresenham(sdl, (t_point){WIN_W / 2 - 25, WIN_H / 2},
	(t_point){WIN_W / 2 - 10, WIN_H / 2}, 0x000000ff);
	bresenham(sdl, (t_point){WIN_W / 2 + 25, WIN_H / 2},
	(t_point){WIN_W / 2 + 10, WIN_H / 2}, 0x000000ff);
	bresenham(sdl, (t_point){WIN_W / 2, WIN_H / 2 + 25},
	(t_point){WIN_W / 2, WIN_H / 2 + 10}, 0x000000ff);
	bresenham(sdl, (t_point){WIN_W / 2, WIN_H / 2 - 25},
	(t_point){WIN_W / 2, WIN_H / 2 - 10}, 0x000000ff);
}

/*
** Draws the sprite contained in s starting at the (x, y) coordinates.
*/

void		draw_sprite(t_sdl *sdl, SDL_Surface *s, int x, int y)
{
	int		i;
	int		x_index;
	int		y_index = 0;
	Uint32	*p;

	SDL_LockSurface(s);
	p = s->pixels;
	i = 0;
	if ((y_index = y) < 0)
		while (y_index < 0)
		{
			y_index++;
			i += s->w;
		}
	while (i < s->w * s->h - 1 && y_index < y + s->h && y_index < WIN_H)
	{
		if ((x_index = x) < 0)
			while (x_index < 0)
			{
				x_index++;
				i++;
			}
		while (x_index < x + s->w)
		{
			if (x_index < WIN_W && (p[i] & 0x000000ff))
				sdl->pix[y_index * WIN_W + x_index] = p[i];
			x_index++;
			i++;
		}
		y_index++;
	}
	s->pixels = p;
	SDL_UnlockSurface(s);
}

/*
** Draws the entire hud (gun, life, ammo)
*/

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
	draw_sprite(sdl, hud->gun[hud->id], 2 * WIN_W / 3,
	WIN_H - hud->gun[hud->id]->h);
	draw_sprite(sdl, hud->ammo, 10, WIN_H - hud->ammo->h - 10);
	draw_sprite(sdl, hud->life, 10, WIN_H - hud->ammo->h - hud->life->h - 20);
	draw_sprite(sdl, hud->nblife, 20 + hud->life->w, WIN_H - hud->ammo->h - (hud->life->h / 2) - 35);
	draw_sprite(sdl, hud->nbammo, 20 + hud->ammo->w, WIN_H - (hud->ammo->h / 2) - 25);
	draw_cross(sdl);
}
