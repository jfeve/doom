/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_items.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 17:39:25 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 12:49:34 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Swaps 2 objects
*/

static void	objs_swap(t_sprite *a, t_sprite *b)
{
	t_sprite	c;

	c = (t_sprite){a->x, a->y, a->type, a->tx, a->tz, a->is_enemy, a->id_rend};
	*a = (t_sprite){b->x, b->y, b->type, b->tx, b->tz, b->is_enemy, b->id_rend};
	*b = (t_sprite){c.x, c.y, c.type, c.tx, c.tz, c.is_enemy, c.id_rend};
}

/*
** Bubble-sort object from nearest to farthest
*/

static void	bubbleSort(t_sprite arr[], int n, t_point player)
{
	int		i;
	int		j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (vector_measure(arr[j].x, arr[j].y, player.x, player.y) >
			vector_measure(arr[i].x, arr[i].y, player.x, player.y))
				objs_swap(&arr[j], &arr[i]);
			j++;
		}
		i++;
	}
}

/*
** Go through every items in the now sector, and stock in drawable the ones that will be drawn
*/

static int	go_through_items(t_sector now, t_mapf *mapf, t_sprite *drawable, int nbdraw)
{
	int		j;
	int		ret;

	ret = nbdraw;
	j = -1;
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
		drawable[ret++] = (t_sprite){now.obj[j].x, now.obj[j].y, now.obj[j].type, tx, tz, 0, now.obj[j].sec};
	}
	return (ret);
}

/*
** Go through every enemies in the now sector, and stock in drawable the ones that will be drawn
*/

static int	go_through_enemies(t_sector now, t_mapf *mapf, t_sprite *drawable, int nbdraw)
{
	int		j;
	int		ret;

	ret = nbdraw;
	j = -1;
	while (++j < now.nbenem && j < MAX_SPRITE)
	{
		if (now.enem[j].life == 0)
			continue;
		float vx = (float)(now.enem[j].x - mapf->player.where.x);
		float vy = (float)(now.enem[j].y - mapf->player.where.y);
		float tx = vx * mapf->player.anglesin - vy * mapf->player.anglecos;
		float tz = vx * mapf->player.anglecos + vy * mapf->player.anglesin;
		if (tz <= 0)
			continue ;
		drawable[ret++] = (t_sprite){now.enem[j].x, now.enem[j].y, now.enem[j].type, tx, tz, 1, now.enem[j].sec};
	}
	return (ret);
}

/*
** Draw the entities' sprites
*/

void		draw_entities(t_mapf *mapf, SDL_Surface *items[4], SDL_Surface *enemy)
{
	int			i;
	int			j;
	t_sprite	drawable[MAX_SPRITE];
	int			nbdraw;
	//float		distance;

	if ((i = mapf->nbrend_s) > MAX_SECT)
		i = MAX_SECT;
	while (--i >= 0)
	{
		t_sector now = mapf->sectors[mapf->rend_s[i].id];
		ft_bzero(drawable, MAX_SPRITE * sizeof(t_sprite));
		nbdraw = 0;
		nbdraw = go_through_items(now, mapf, drawable, nbdraw);
		nbdraw = go_through_enemies(now, mapf, drawable, nbdraw);
		bubbleSort(drawable, nbdraw, (t_point){mapf->player.where.x, mapf->player.where.y});
		j = -1;
		while (++j < nbdraw && j < MAX_SPRITE)
		{
			int type = drawable[j].type - 1;
			float xscale = HFOV / drawable[j].tz;
			float yscale = VFOV / drawable[j].tz;
			int x = (drawable[j].tx * xscale) * -1 + WIN_W / 2;
			int y = (WIN_H / 2) - (int)(YAW(now.floor - mapf->player.where.z, drawable[j].tz, mapf->player.yaw) * yscale);
			dprintf(1, "%");
			if (x > mapf->rend_s[drawable[j].id_rend].beginx && x < mapf->rend_s[drawable[j].id_rend].endx)
				continue ;
			float distance = vector_measure(drawable[j].x, drawable[j].y, mapf->player.where.x, mapf->player.where.y);
			if (distance == 0.0f)
				distance = 0.0001f;
			if (drawable[j].is_enemy)
				draw_sprite_resize(&mapf->sdl, enemy, (t_point){x - (enemy->w / 2), y - (enemy->h / 2)},
				(t_point){(int)((float)enemy->w * (32 / (distance))), (int)((float)enemy->h * (32 / (distance)))});
			else
				draw_sprite_resize(&mapf->sdl, items[type], (t_point){x - (items[type]->w / 2), y - (items[type]->h / 2)},
				(t_point){(int)((float)items[type]->w * (16 / (distance))), (int)((float)items[type]->h * (16 / (distance)))});
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
			int x = (tx * xscale) * -1 + RWIN_W / 2;
			int y = (RWIN_H / 2) - (int)(YAW(now.floor - mapf->player.where.z, tz, mapf->player.yaw) * yscale);
			draw_sprite(&mapf->sdl, s, x - (s->w / 2), y - (s->h / 2));
		}
	}*/
