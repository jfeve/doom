/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_items.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 17:39:25 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 15:07:29 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Draw the entities' sprites
*/

static void	find_drawable(t_mapf *mapf, t_sector *now, t_sprite *drawable,
t_point *p)
{
	t_float	v;
	t_float	t;

	p->x = go_through_items(*now, mapf->player, drawable, p->x);
	p->x = go_through_enemies(*now, mapf->player, drawable, p->x);
	if (p->y == mapf->finish_sec && p->x < MAX_SPRITE - 1)
	{
		v.x = (float)(mapf->finish_x - mapf->player.where.x);
		v.y = (float)(mapf->finish_y - mapf->player.where.y);
		t.x = v.x * mapf->player.anglesin - v.y * mapf->player.anglecos;
		t.y = v.x * mapf->player.anglecos + v.y * mapf->player.anglesin;
		if (t.y > 0)
			drawable[(p->x)++] = (t_sprite){mapf->finish_x, mapf->finish_y,
			9, t.x, t.y, 0};
	}
	bubble_sort(drawable, p->x, (t_point){mapf->player.where.x,
	mapf->player.where.y});
}

static int	norm(t_norm *n, t_input *in, t_mapf *mapf, SDL_Surface *enemy[2])
{
	if (n->drawable[n->j].is_enemy == 0 && n->type < 8
	&& fmodf(mapf->player.angle, 2 * M_PI) >= M_PI
	&& fmodf(mapf->player.angle, 2 * M_PI) <= (2 * M_PI))
		n->type += 4;
	n->x = (n->drawable[n->j].tx * n->xscale) * -1 + RWIN_W / 2;
	n->y = (RWIN_H / 2) - (int)(yaw(n->now->floor - mapf->player.where.z,
	n->drawable[n->j].tz, mapf->player.yaw) * n->yscale);
	if (n->x > mapf->rend_s[n->i].endx || n->x < mapf->rend_s[n->i].beginx)
		return (0);
	n->distance = vector_measure(n->drawable[n->j].x, n->drawable[n->j].y,
	mapf->player.where.x, mapf->player.where.y);
	if (n->distance == 0.0f)
		n->distance = 0.0001f;
	if (in->mouse[SDL_BUTTON_LEFT] && mapf->player.ammo != 0)
	{
		if (kill_enemies(n->now, n->drawable[n->j], enemy,
		(t_xyz){(float)n->x, (float)n->y, n->distance}))
		{
			in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
			(n->j)++;
			return (0);
		}
	}
	return (1);
}

static void	norm2(t_norm *n, SDL_Surface *items[9], SDL_Surface *enemy[2],
t_mapf *mapf)
{
	if (n->drawable[n->j].is_enemy == 1)
		draw_sprite_resize(&mapf->sdl, enemy[n->type], (t_point){n->x
		- (enemy[n->type]->w / 2), n->y - (enemy[n->type]->h / 2) - (1300.0f
		/ n->distance)}, (t_point){(int)((float)enemy[n->type]->w * (32
		/ (n->distance))), (int)((float)enemy[n->type]->h * (32
		/ (n->distance)))});
	else
		draw_sprite_resize(&mapf->sdl, items[n->type], (t_point){n->x
		- (items[n->type]->w / 2), n->y - (items[n->type]->h / 2)},
		(t_point){(int)((float)items[n->type]->w * (16 / (n->distance))),
		(int)((float)items[n->type]->h * (16 / (n->distance)))});
}

void		draw_entities(t_mapf *mapf, SDL_Surface *items[9],
SDL_Surface *enemy[2], t_input *in)
{
	t_norm	n;

	if ((n.i = mapf->nbrend_s) > MAX_SECT)
		n.i = MAX_SECT;
	while (--n.i >= 0)
	{
		n.now = &mapf->sectors[mapf->rend_s[n.i].id];
		ft_bzero(n.drawable, MAX_SPRITE * sizeof(t_sprite));
		n.nbdraw = 0;
		n.p = (t_point){n.nbdraw, mapf->rend_s[n.i].id};
		find_drawable(mapf, n.now, n.drawable, &n.p);
		n.nbdraw = n.p.x;
		n.j = -1;
		while (++n.j < n.nbdraw && n.j < MAX_SPRITE)
		{
			n.type = n.drawable[n.j].type - 1;
			n.xscale = HFOV / n.drawable[n.j].tz;
			n.yscale = VFOV / n.drawable[n.j].tz;
			if (!(norm(&n, in, mapf, enemy)))
				continue ;
			norm2(&n, items, enemy, mapf);
		}
	}
}
