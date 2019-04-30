/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_items.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 17:39:25 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 18:17:07 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	objs_swap(t_objs *a, t_objs *b)
{
	t_objs	c;

	c = *a;
	*a = *b;
	*b = c;
}

static void	quickSort(t_objs *objs, int low, int high, t_point player)
{
	if (low < high)
	{
		t_objs pivot = objs[high];
		int i = (low - 1);
		for (int j = low; j <= high- 1; j++)
		{
			if ()
			{
				i++;
				objs_swap(&objs[i], &objs[j]);
			}
			dprintf(1, "%d   %d   %d   %d\n", (int)fabs((float)(objs[j].x - player.x)), (int)fabs((float)(pivot.x - player.x)),
			(int)fabs((float)(objs[j].y - player.y)), (int)fabs((float)(pivot.y - player.y)));
		}
		objs_swap(&objs[i + 1], &objs[high]);
		int pi = i + 1;
		quickSort(objs, low, pi - 1, player);
		quickSort(objs, pi + 1, high, player);
	}
}

void		draw_items(t_mapf *mapf, SDL_Surface *s)
{
	int		i;
	int		j;

	i = mapf->nbrend_s;
	while (--i >= 0)
	{
		j = -1;
		t_sector now = mapf->sectors[mapf->rend_s[i]];
		while (++j < now.nbobjs)
		{
			float vx = (float)(now.obj[j].x - mapf->player.where.x);
			float vy = (float)(now.obj[j].y - mapf->player.where.y);
			float tx = vx * mapf->player.anglesin - vy * mapf->player.anglecos;
			float tz = vx * mapf->player.anglecos + vy * mapf->player.anglesin;
			//if (tz >= 0)
			float xscale = HFOV / tz;
			//float yscale = VFOV / tz;
			int x = (tx * xscale) * -1 + WIN_W / 2;
			//int y = WIN_H / 2 - (int)(Yaw(yceil, tz1) * yscale1);
			draw_sprite(&mapf->sdl, s, x - (s->w / 2), (WIN_H / 2) - (s->h / 2));
		}
	}
}
