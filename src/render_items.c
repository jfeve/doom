/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_items.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 17:39:25 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 17:09:32 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	objs_swap(t_odraw *a, t_odraw *b)
{
	t_odraw	c;

	c = (t_odraw){(t_objs){a->o.x, a->o.y, a->o.hitbox, a->o.type, a->o.sec}, a->tx, a->tz};
	*a = (t_odraw){(t_objs){b->o.x, b->o.y, b->o.hitbox, b->o.type, b->o.sec}, b->tx, b->tz};
	*b = (t_odraw){(t_objs){c.o.x, c.o.y, c.o.hitbox, c.o.type, c.o.sec}, c.tx, c.tz};
}

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
			float vx = (float)(now.obj[j].x - mapf->player.where.x);
			float vy = (float)(now.obj[j].y - mapf->player.where.y);
			float tx = vx * mapf->player.anglesin - vy * mapf->player.anglecos;
			float tz = vx * mapf->player.anglecos + vy * mapf->player.anglesin;
			dprintf(1, "%d   %d\n", j, now.nbobjs);
			if (tz <= 0)
				continue ;
			drawable[nbdraw++] = (t_odraw){(t_objs){now.obj[j].x, now.obj[j].y, now.obj[j].hitbox, now.obj[j].type, now.obj[j].sec}, tx, tz};
		}
		bubbleSort(drawable, nbdraw, (t_point){mapf->player.where.x, mapf->player.where.y});
		j = -1;
		while (++j < nbdraw && j < MAX_SPRITE)
		{
			float xscale = HFOV / drawable[j].tz;
			float yscale = VFOV / drawable[j].tz;
			int x = (drawable[j].tx * xscale) * -1 + WIN_W / 2;
			int y = (WIN_H / 2) - (int)(YAW(now.floor - mapf->player.where.z, drawable[j].tz, mapf->player.yaw) * yscale);
			draw_sprite(&mapf->sdl, s, x - (s->w / 2), y - (s->h / 2));
		}
	}
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