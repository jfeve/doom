/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_draw_screen.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 16:27:38 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:49:02 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

Uint32		add_light(Uint32 color)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;

	r = color >> 24;
	g = color >> 16;
	b = color >> 8;
	a = color;
	if (r * 1.8 < 255)
		r *= 1.8;
	else
		r = 255;
	if (g * 1.8 < 255)
		g *= 1.8;
	else
		g = 255;
	if (b * 1.8 < 255)
		b *= 1.8;
	else
		b = 255;
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

void		draw(t_mapf *mapf, t_point xx, t_point yy, t_sector *sect)
{
	int		y;

	y = 0;
	yy.x = clamp(yy.x, 0, RWIN_H - 1);
	yy.y = clamp(yy.y, 0, RWIN_H - 1);
	if (yy.y == yy.x)
		mapf->sdl.pix[yy.x * RWIN_W + xx.x] = xx.y;
	else if (yy.y > yy.x)
	{
		y = yy.x;
		while (y <= yy.y)
		{
			if (sect->lum == 1)
				mapf->sdl.pix[y * RWIN_W + xx.x] = add_light(xx.y);
			else
				mapf->sdl.pix[y * RWIN_W + xx.x] = xx.y;
			y++;
		}
	}
}

void		draw_text(t_mapf *mapf, t_ren *ren, t_quad qu, t_sector *sect)
{
	Uint32	*p;
	int		y;
	int		cyb;
	float	tey;
	int		ind;

	y = clamp(qu.ya, ren->ytop[qu.x], ren->ybot[qu.x]);
	cyb = clamp(qu.yb, ren->ytop[qu.x], ren->ybot[qu.x]);
	ind = sect->vert[qu.s].text - 1;
	SDL_LockSurface(mapf->wall[ind]);
	p = mapf->wall[ind]->pixels;
	while (y < cyb)
	{
		tey = (float)((float)y - (float)qu.ya) / (float)((float)qu.yb -
				(float)qu.ya);
		tey = mapf->wall[ind]->h * tey;
		if (sect->lum == 1)
			mapf->sdl.pix[y * RWIN_W + qu.x] = add_light(p[ren->xx.tx % 199
					+ (int)tey * mapf->wall[ind]->w]);
		else
			mapf->sdl.pix[y * RWIN_W + qu.x] = p[ren->xx.tx % 199 + (int)tey
				* mapf->wall[ind]->w];
		y++;
	}
}
