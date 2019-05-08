/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_move3.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 17:17:03 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 17:55:49 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	norm(t_mapf *mapf, t_float d, t_point *xety, t_float *proj)
{
	t_float	b;
	t_float	p;

	p.x = mapf->player.where.x;
	p.y = mapf->player.where.y;
	xety->x = d.y / d.x;
	xety->y = mapf->player.where.y - xety->x * mapf->player.where.x;
	b = (t_float){mapf->player.where.x + 2, xety->x
	* (mapf->player.where.x + 2) + xety->y};
	proj->x = ((mapf->player.velo.x * (b.x - p.x)
	+ mapf->player.velo.y * (b.y - p.y)) / vector_measure(p.x, p.y, b.x, b.y)
	* vector_measure(p.x, p.y, b.x, b.y) * (b.x - p.x));
	proj->y = ((mapf->player.velo.x * (b.x - p.x)
	+ mapf->player.velo.y * (b.y - p.y)) / vector_measure(p.x, p.y, b.x, b.y)
	* vector_measure(p.x, p.y, b.x, b.y) * (b.y - p.y));
	mapf->player.where.x += proj->x / 4;
	mapf->player.where.y += proj->y / 4;
}

void		slide_wall(t_mapf *mapf, int i)
{
	t_float		d;
	t_point		xety;
	t_sector	*sec;
	t_float		proj;

	xety = (t_point){0, 0};
	sec = &mapf->sectors[mapf->player.sect];
	if (i != sec->nbvert - 1)
		d = (t_float){sec->vert[i + 1].x - sec->vert[i].x, sec->vert[i + 1].y
		- sec->vert[i].y};
	else
		d = (t_float){sec->vert[0].x - sec->vert[i].x, sec->vert[0].y
		- sec->vert[i].y};
	if (d.x == 0)
	{
		xety.x = sec->vert[i].x;
		mapf->player.where.y += mapf->player.velo.y;
	}
	else if (d.y == 0)
	{
		xety.y = sec->vert[i].y;
		mapf->player.where.x += mapf->player.velo.x;
	}
	else
		norm(mapf, d, &xety, &proj);
}

static void	events(float *move_vec, t_mapf *mapf, t_input *in)
{
	if (in->key[SDL_SCANCODE_W])
	{
		move_vec[0] += mapf->player.anglecos * 0.2f;
		move_vec[1] += mapf->player.anglesin * 0.2f;
	}
	if (in->key[SDL_SCANCODE_S])
	{
		move_vec[0] -= mapf->player.anglecos * 0.2f;
		move_vec[1] -= mapf->player.anglesin * 0.2f;
	}
	if (in->key[SDL_SCANCODE_A])
	{
		move_vec[0] += mapf->player.anglesin * 0.2f;
		move_vec[1] -= mapf->player.anglecos * 0.2f;
	}
	if (in->key[SDL_SCANCODE_D])
	{
		move_vec[0] -= mapf->player.anglesin * 0.2f;
		move_vec[1] += mapf->player.anglecos * 0.2f;
	}
}

void		move_chara(t_mapf *mapf, t_input *in)
{
	float	move_vec[2];
	float	acc;
	t_float	tmp;

	move_vec[0] = 0.0f;
	move_vec[1] = 0.0f;
	acc = 0.2f;
	events(move_vec, mapf, in);
	tmp = (t_float){mapf->player.velo.x, mapf->player.velo.y};
	mapf->player.velo.x = mapf->player.velo.x * (1 - acc) + move_vec[0]
	* acc;
	mapf->player.velo.y = mapf->player.velo.y * (1 - acc) + move_vec[1]
	* acc;
	if (check_horcoll(mapf) == 0)
	{
		mapf->player.where.x += mapf->player.velo.x * mapf->coeff;
		mapf->player.where.y += mapf->player.velo.y * mapf->coeff;
	}
}
