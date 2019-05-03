/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_items.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 17:39:25 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 15:45:29 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Resize a sprite and draw it.
** start is the starting point to draw, size is the width and height of the resized pic
*/

void		draw_sprite_resize(t_sdl *sdl, SDL_Surface *s, t_point start, t_point size)
{
	int		x_index;
	int		y_index;
	int		x_ratio;
	int		y_ratio;
	int		x2;
	int		y2;
	Uint32	*p;

	SDL_LockSurface(s);
	p = s->pixels;
	x_ratio = (int)((s->w << 16) / size.x) + 1;
	y_ratio = (int)((s->h << 16) / size.y) + 1;
	if ((y_index = start.y) < 0)
		while (y_index < 0)
			y_index++;
	while (y_index < start.y + size.y && y_index < WIN_H)
	{
		if ((x_index = start.x) < 0)
			while (x_index < 0)
				x_index++;
		while (x_index < start.x + size.x && x_index < WIN_W)
		{
			if (x_index < WIN_W)
			{
				x2 = (((x_index - start.x) * x_ratio) >> 16);
				y2 = (((y_index - start.y) * y_ratio) >> 16);
				if (p[y2 * s->w + x2] & 0x000000ff)
					sdl->pix[y_index * WIN_W + x_index] = p[y2 * s->w + x2];
			}
			x_index++;
		}
		y_index++;
	}
	s->pixels = p;
	SDL_UnlockSurface(s);
}

/*
** Swaps 2 objects
*/

static void	objs_swap(t_odraw *a, t_odraw *b)
{
	t_odraw	c;

	c = (t_odraw){(t_objs){a->o.x, a->o.y, a->o.hitbox, a->o.type, a->o.sec, a->o.picked}, a->tx, a->tz};
	*a = (t_odraw){(t_objs){b->o.x, b->o.y, b->o.hitbox, b->o.type, b->o.sec, b->o.picked}, b->tx, b->tz};
	*b = (t_odraw){(t_objs){c.o.x, c.o.y, c.o.hitbox, c.o.type, c.o.sec, c.o.picked}, c.tx, c.tz};
}

/*
** Bubble-sort object from nearest to farthest
*/

static void	bubbleSort(t_odraw arr[], int n, t_point player)
{
	int		i;
	int		j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (vector_measure(arr[j].o.x, arr[j].o.y, player.x, player.y) >
			vector_measure(arr[i].o.x, arr[i].o.y, player.x, player.y))
				objs_swap(&arr[j], &arr[i]);
			j++;
		}
		i++;
	}
}

/*
** Draw the items' sprites
*/

void		draw_items(t_mapf *mapf, SDL_Surface *s)
{
	int		i;
	int		j;
	t_odraw	drawable[MAX_SPRITE];
	int		nbdraw;

	;
	if ((i = mapf->nbrend_s) > MAX_SECT)
		i = MAX_SECT;
	while (--i >= 0)
	{
		j = -1;
		t_sector now = mapf->sectors[mapf->rend_s[i]];
		ft_bzero(drawable, MAX_SPRITE * sizeof(t_odraw));
		nbdraw = 0;
		while (++j < now.nbobjs && j < MAX_SPRITE)
		{
			if (now.obj[j].picked == 1)
				continue;
			float vx = (float)(now.obj[j].x - mapf->player.where.x);
			float vy = (float)(now.obj[j].y - mapf->player.where.y);
			float tx = vx * mapf->player.anglesin - vy * mapf->player.anglecos;
			float tz = vx * mapf->player.anglecos + vy * mapf->player.anglesin;
			if (tz <= 0)
				continue ;
			drawable[nbdraw++] = (t_odraw){(t_objs){now.obj[j].x, now.obj[j].y, now.obj[j].hitbox, now.obj[j].type, now.obj[j].sec, now.obj[j].picked}, tx, tz};
		}
		bubbleSort(drawable, nbdraw, (t_point){mapf->player.where.x, mapf->player.where.y});
		j = -1;
		while (++j < nbdraw && j < MAX_SPRITE)
		{
			float xscale = HFOV / drawable[j].tz;
			float yscale = VFOV / drawable[j].tz;
			int x = (drawable[j].tx * xscale) * -1 + WIN_W / 2;
			int y = (WIN_H / 2) - (int)(YAW(now.floor - mapf->player.where.z, drawable[j].tz, mapf->player.yaw) * yscale);
			float distance = vector_measure(drawable[j].o.x, drawable[j].o.y, mapf->player.where.x, mapf->player.where.y);
			dprintf(1, "%f   %f\n", distance, 16.0f / distance);
			if (distance == 0.0f)
				distance = 0.0001f;
			draw_sprite_resize(&mapf->sdl, s, (t_point){x - (s->w / 2), y - (2 * s->h / 3)},
			(t_point){(int)((float)s->w * (16.0f / distance)), (int)((float)s->h * (16.0f / distance))});
		}
	}
	dprintf(1, "\n");
}

/*int		i;
	int		j;

	i = mapf->nbrend_s;
	while (--i >= 0)
	{
		j = -1;
		t_sector now = mapf->sectors[mapf->rend_s[i]];
		bubbleSort(now.obj, now.nbobjs, (t_point){mapf->player.where.x, mapf->player.where.y});
		while (++j < now.nbobjs)
		{
			float vx = (float)(now.obj[j].x - mapf->player.where.x);
			float vy = (float)(now.obj[j].y - mapf->player.where.y);
			float tx = vx * mapf->player.anglesin - vy * mapf->player.anglecos;
			float tz = vx * mapf->player.anglecos + vy * mapf->player.anglesin;
			if (j == 0) dprintf(1, "%f   %d %d   %f %f\n\n", tz, now.obj[j].x,
			now.obj[j].y, mapf->player.where.x, mapf->player.where.y);
			if (tz <= 0)
				continue ;
			float xscale = HFOV / tz;
			float yscale = VFOV / tz;
			int x = (tx * xscale) * -1 + WIN_W / 2;
			int y = (WIN_H / 2) - (int)(YAW(now.floor - mapf->player.where.z, tz, mapf->player.yaw) * yscale);
			draw_sprite(&mapf->sdl, s, x - (s->w / 2), y - (s->h / 2));
		}
	}*/