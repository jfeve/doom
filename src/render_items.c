/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_items.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 17:39:25 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 18:59:58 by flombard    ###    #+. /#+    ###.fr     */
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

static void	bubbleSort(t_objs arr[], int n, t_point player)
{
	int		i;
	int		j;

	i = -1;
	while (++i < n - 1)
	{
		j = i;
		while (++j < n - 1)
			if (vector_measure(arr[j].x, arr[j].y, player.x, player.y) < vector_measure(arr[j + 1].x, arr[j + 1].y, player.x, player.y))
				objs_swap(&arr[j], &arr[j+1]);
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
		bubbleSort(now.obj, now.nbobjs, (t_point){mapf->player.where.x, mapf->player.where.y});
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
