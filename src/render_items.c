/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_items.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 17:39:25 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 12:36:28 by flombard    ###    #+. /#+    ###.fr     */
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

	c = (t_sprite){a->x, a->y, a->type, a->tx, a->tz, a->is_enemy};
	*a = (t_sprite){b->x, b->y, b->type, b->tx, b->tz, b->is_enemy};
	*b = (t_sprite){c.x, c.y, c.type, c.tx, c.tz, c.is_enemy};
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

static int	go_through_items(t_sector now, t_player player, t_sprite *drawable, int nbdraw)
{
	int		j;
	int		ret;

	ret = nbdraw;
	j = -1;
	while (++j < now.nbobjs && j < MAX_SPRITE)
	{
		if (now.obj[j].picked == 1)
			continue;
		float vx = (float)(now.obj[j].x - player.where.x);
		float vy = (float)(now.obj[j].y - player.where.y);
		float tx = vx * player.anglesin - vy * player.anglecos;
		float tz = vx * player.anglecos + vy * player.anglesin;
		if (tz <= 0)
			continue ;
		drawable[ret++] = (t_sprite){now.obj[j].x, now.obj[j].y, now.obj[j].type, tx, tz, 0};
	}
	return (ret);
}

/*
** Go through every enemies in the now sector, and stock in drawable the ones that will be drawn
*/

int			go_through_enemies(t_sector now, t_player player, t_sprite *drawable, int nbdraw)
{
	int		j;
	int		ret;

	ret = nbdraw;
	j = -1;
	while (++j < now.nbenem && j < MAX_SPRITE)
	{
		if (now.enem[j].life == 0)
			continue;
		float vx = (float)(now.enem[j].x - player.where.x);
		float vy = (float)(now.enem[j].y - player.where.y);
		float tx = vx * player.anglesin - vy * player.anglecos;
		float tz = vx * player.anglecos + vy * player.anglesin;
		if (tz <= 0)
			continue ;
		drawable[ret++] = (t_sprite){now.enem[j].x, now.enem[j].y, now.enem[j].type, tx, tz, 1};
	}
	return (ret);
}

/*
** Draw the entities' sprites
*/

void		draw_entities(t_mapf *mapf, SDL_Surface *items[9], SDL_Surface *enemy[2], t_input *in)
{
	int			i;
	int			j;
	t_sprite	drawable[MAX_SPRITE];
	int			nbdraw;

	if ((i = mapf->nbrend_s) > MAX_SECT)
		i = MAX_SECT;
	while (--i >= 0)
	{
		t_sector *now = &mapf->sectors[mapf->rend_s[i].id];
		ft_bzero(drawable, MAX_SPRITE * sizeof(t_sprite));
		nbdraw = 0;
		nbdraw = go_through_items(*now, mapf->player, drawable, nbdraw);
		nbdraw = go_through_enemies(*now, mapf->player, drawable, nbdraw);
		if (mapf->rend_s[i].id == mapf->finish_sec && nbdraw < MAX_SPRITE - 1)
		{
			float vx = (float)(mapf->finish_x - mapf->player.where.x);
			float vy = (float)(mapf->finish_y - mapf->player.where.y);
			float tx = vx * mapf->player.anglesin - vy * mapf->player.anglecos;
			float tz = vx * mapf->player.anglecos + vy * mapf->player.anglesin;
			if (tz > 0)
				drawable[nbdraw++] = (t_sprite){mapf->finish_x, mapf->finish_y, 9, tx, tz, 0};
		}
		bubbleSort(drawable, nbdraw, (t_point){mapf->player.where.x, mapf->player.where.y});
		j = -1;
		while (++j < nbdraw && j < MAX_SPRITE)
		{
			int type = drawable[j].type - 1;
			if (drawable[j].is_enemy == 0 && type < 8 && fmodf(mapf->player.angle, 2 * M_PI) >= M_PI && fmodf(mapf->player.angle, 2 * M_PI) <= (2 * M_PI))
				type += 4;
			float xscale = HFOV / drawable[j].tz;
			float yscale = VFOV / drawable[j].tz;
			int x = (drawable[j].tx * xscale) * -1 + RWIN_W / 2;
			int y = (RWIN_H / 2) - (int)(yaw(now->floor - mapf->player.where.z, drawable[j].tz, mapf->player.yaw) * yscale);
			if (x > mapf->rend_s[i].endx || x < mapf->rend_s[i].beginx)
				continue ;
			/*if (type == 8 && (x > mapf->rend_s[mapf->finish_sec].endx || x < mapf->rend_s[mapf->finish_sec].beginx))
				continue ;*/
			float distance = vector_measure(drawable[j].x, drawable[j].y, mapf->player.where.x, mapf->player.where.y);
			if (distance == 0.0f)
				distance = 0.0001f;
			if (in->mouse[SDL_BUTTON_LEFT] && mapf->player.ammo != 0)
			{
				if (kill_enemies(now, drawable[j], enemy, (t_point){x, y}, distance))
				{
					in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
					j++;
					continue ;
				}
			}
			if (drawable[j].is_enemy == 1)
				draw_sprite_resize(&mapf->sdl, enemy[type], (t_point){x - (enemy[type]->w / 2), y - (enemy[type]->h / 2) - (1300.0f / distance)},
				(t_point){(int)((float)enemy[type]->w * (32 / (distance))), (int)((float)enemy[type]->h * (32 / (distance)))});
			else
				draw_sprite_resize(&mapf->sdl, items[type], (t_point){x - (items[type]->w / 2), y - (items[type]->h / 2)},
				(t_point){(int)((float)items[type]->w * (16 / (distance))), (int)((float)items[type]->h * (16 / (distance)))});
		}
	}
}
