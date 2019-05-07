/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_sprite_draw.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 21:59:52 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 22:32:06 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Draws the sprite contained in s starting at the (x, y) coordinates.
*/

static void	init_index(int *dest, int src, int *i, int incr)
{
	if ((*dest = src) < 0)
		while (*dest < 0)
		{
			(*dest)++;
			*i += incr;
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

void		draw_sprite_resize(t_sdl *sdl, SDL_Surface *s,
t_point start, t_point size)
{
	t_point	index;
	t_point	ratio;
	int		x2;
	int		y2;
	Uint32	*p;

	if (SDL_MUSTLOCK(s))
		SDL_LockSurface(s);
	p = s->pixels;
	ratio.x = (int)((s->w << 16) / size.x) + 1;
	ratio.y = (int)((s->h << 16) / size.y) + 1;
	if ((index.y = start.y) < 0)
		while (index.y < 0)
			index.y++;
	while (index.y < start.y + size.y && index.y < RWIN_H)
	{
		if ((index.x = start.x) < 0)
			while (index.x < 0)
				index.x++;
		while (index.x < start.x + size.x && index.x < RWIN_W)
		{
			if (index.x < RWIN_W)
			{
				x2 = (((index.x - start.x) * ratio.x) >> 16);
				y2 = (((index.y - start.y) * ratio.y) >> 16);
				if (p[y2 * s->w + x2] & 0x000000ff)
					sdl->pix[index.y * RWIN_W + index.x] = p[y2 * s->w + x2];
			}
			index.x++;
		}
		index.y++;
	}
	s->pixels = p;
	if (SDL_MUSTLOCK(s))
		SDL_UnlockSurface(s);
}
