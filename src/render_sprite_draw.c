/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_sprite_draw.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 21:59:52 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 11:08:11 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Draws the sprite contained in s starting at the (x, y) coordinates.
*/

static void	init_index(int *dest, int src, int *i, int incr)
{
	if (i != NULL)
	{
		if ((*dest = src) < 0)
			while (*dest < 0)
			{
				(*dest)++;
				*i += incr;
			}
	}
	else
	{
		if ((*dest = src) < 0)
			while (*dest < 0)
				(*dest)++;
	}
}

void		draw_sprite(t_sdl *sdl, SDL_Surface *s, int x, int y)
{
	int		i;
	t_point	index;
	Uint32	*p;

	if (SDL_MUSTLOCK(s))
		SDL_LockSurface(s);
	p = s->pixels;
	i = 0;
	init_index(&index.y, y, &i, s->w);
	while (i < s->w * s->h - 1 && index.y < y + s->h && index.y < RWIN_H)
	{
		init_index(&index.x, x, &i, 1);
		while (index.x < x + s->w)
		{
			if (index.x < RWIN_W && (p[i] & 0x000000ff))
				sdl->pix[index.y * RWIN_W + index.x] = p[i];
			index.x++;
			i++;
		}
		index.y++;
	}
	s->pixels = p;
	if (SDL_MUSTLOCK(s))
		SDL_UnlockSurface(s);
}

/*
** Resize a sprite and draw it.
** start is the starting point to draw,
** size is the width and height of the resized pic
*/

static void	fill_pixels(t_sdl *sdl, SDL_Surface *s, Uint32 *p, t_line norm)
{
	if (p[norm.dy * s->w + norm.dx] & 0x000000ff)
		sdl->pix[norm.sy * RWIN_W + norm.sx] = p[norm.dy * s->w + norm.dx];
}

void		draw_sprite_resize(t_sdl *sdl, SDL_Surface *s,
t_point start, t_point size)
{
	t_point	index;
	t_point	ratio;
	Uint32	*p;

	if (SDL_MUSTLOCK(s))
		SDL_LockSurface(s);
	p = s->pixels;
	ratio.x = (int)((s->w << 16) / size.x) + 1;
	ratio.y = (int)((s->h << 16) / size.y) + 1;
	init_index(&index.y, start.y, NULL, 0);
	while (index.y < start.y + size.y && index.y < RWIN_H)
	{
		init_index(&index.x, start.x - 1, NULL, 0);
		while (++index.x < start.x + size.x && index.x < RWIN_W)
			if (index.x < RWIN_W)
				fill_pixels(sdl, s, p, (t_line){.dx = (((index.x - start.x)
				* ratio.x) >> 16), .dy = (((index.y - start.y) * ratio.y)
				>> 16), .sx = index.x, .sy = index.y});
		index.y++;
	}
	s->pixels = p;
	if (SDL_MUSTLOCK(s))
		SDL_UnlockSurface(s);
}
