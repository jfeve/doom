/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_move.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 09:32:13 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 17:55:11 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void		slide_wall(t_mapf *mapf, int i)
{
	float		dx;
	float		dy;
	float		x;
	float		y;
	t_sector	*sec;
	t_float		proj;

	x = 0;
	y = 0;
	sec = &mapf->sectors[mapf->player.sect];
	if (i != sec->nbvert - 1)
	{
		dx = sec->vert[i + 1].x - sec->vert[i].x;
		dy = sec->vert[i + 1].y - sec->vert[i].y;
	}
	else
	{
		dx = sec->vert[0].x - sec->vert[i].x;
		dy = sec->vert[0].y - sec->vert[i].y;
	}
	if (dx == 0)
	{
		x = sec->vert[i].x;
		mapf->player.where.y += mapf->player.velo.y;
	}
	else if (dy == 0)
	{
		y = sec->vert[i].y;
		mapf->player.where.x += mapf->player.velo.x;
	}
	else
	{
		float	px = mapf->player.where.x;
		float	py = mapf->player.where.y;
		x = dy / dx;
		y = mapf->player.where.y - x * mapf->player.where.x;
		t_float		b;
		b = (t_float){mapf->player.where.x + 2, x *
			(mapf->player.where.x + 2) + y};
		proj.x = ((mapf->player.velo.x * (b.x - px) +
				mapf->player.velo.y * (b.y - py)) / vector_measure(px, py, b.x, b.y) *
				vector_measure(px, py, b.x, b.y) * (b.x - px));
		proj.y = ((mapf->player.velo.x * (b.x - px) +
				mapf->player.velo.y * (b.y - py)) / vector_measure(px, py, b.x, b.y) *
				vector_measure(px, py, b.x, b.y) * (b.y - py));
		mapf->player.where.x += proj.x / 4;
		mapf->player.where.y += proj.y / 4;
	}
}

int			check_port(t_mapf *mapf, int i, t_sector *sect)
{
	float	ps;
	float	ps2;
	float	px = mapf->player.where.x;
	float	py = mapf->player.where.y;
	float	dx = mapf->player.velo.x;
	float	dy = mapf->player.velo.y;

	if (i != sect->nbvert - 1)
	{
		ps = f_pointside((t_float){px, py}, (t_float){sect->vert[i].x, sect->vert[i].y},
			(t_float){sect->vert[i + 1].x, sect->vert[i + 1].y});
		ps2 = f_pointside((t_float){px + dx, py + dy}, (t_float){sect->vert[i].x, sect->vert[i].y},
			(t_float){sect->vert[i + 1].x, sect->vert[i + 1].y});
	}
	else
	{
		ps = f_pointside((t_float){px, py}, (t_float){sect->vert[i].x, sect->vert[i].y},
			(t_float){sect->vert[0].x, sect->vert[0].y});
		ps2 = f_pointside((t_float){px + dx, py + dy}, (t_float){sect->vert[i].x, sect->vert[i].y},
			(t_float){sect->vert[0].x, sect->vert[0].y});
	}
	if ((ps >= fabs(dx * 4) && ps2 <= fabs(dx * 4)) || (ps <= fabs(dx * 4) && ps2 >= fabs(dx * 4)))
	{
		if (mapf->player.where.z - mapf->player.eye + KNEE > mapf->sectors[sect->vert[i].neigh].floor &&
				mapf->player.where.z < mapf->sectors[sect->vert[i].neigh].ceil)
		{
			if (mapf->player.state != jumping && mapf->player.state != flying && mapf->player.state != crouching)
				mapf->player.state = falling;
			if (mapf->player.state == flying || mapf->player.state == jumping || mapf->player.state == falling)
				mapf->player.add_z -= mapf->sectors[sect->vert[i].neigh].floor - mapf->sectors[mapf->player.sect].floor;
			mapf->sectors[mapf->player.sect].lum = 0;
			mapf->player.sect = sect->vert[i].neigh;
			mapf->sectors[mapf->player.sect].lum = 1;
			return (0);
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

t_float		vmp_compute(t_sector *sect, t_float p, t_float d, t_point i)
{
	t_float	vmp;

	vmp.x = vector_measure(sect->vert[i.x].x, sect->vert[i.x].y, p.x, p.y) +
			vector_measure(sect->vert[i.y].x, sect->vert[i.y].y, p.x, p.y);
	vmp.y = vector_measure(sect->vert[i.x].x, sect->vert[i.x].y, p.x + d.x, p.y + d.y ) +
			vector_measure(sect->vert[i.y].x, sect->vert[i.y].y, p.x + d.x, p.y + d.y);
	return (vmp);
}

int			vm_check(t_mapf *mapf, int i, t_sector *sect)
{
	t_float	p;
	t_float	d;
	t_float	vmp;
	float	vmw;

	p = (t_float){mapf->player.where.x, mapf->player.where.y};
	d = (t_float){mapf->player.velo.x, mapf->player.velo.y};
	if (i < sect->nbvert - 1)
	{
		vmw = vector_measure(sect->vert[i].x, sect->vert[i].y, sect->vert[i + 1].x, sect->vert[i + 1].y);
		vmp = vmp_compute(sect, p, d, (t_point){i, i + 1});
	}
	else
	{
		vmw = vector_measure(sect->vert[i].x, sect->vert[i].y, sect->vert[0].x, sect->vert[0].y);
		vmp = vmp_compute(sect, p, d, (t_point){i, 0});
	}
	return (vmp.x > vmp.y && vmp.y <= vmw + 0.1);
}

int			check_near_edge(t_mapf *mapf, int i, t_sector *sect)
{
	t_float	p;
	float	vmfi;
	float	vmse;

	p = (t_float){mapf->player.where.x, mapf->player.where.y};
	vmfi = vector_measure(sect->vert[i].x, sect->vert[i].y, p.x, p.y);
	if (i < sect->nbvert - 1)
		vmse = vector_measure(sect->vert[i + 1].x, sect->vert[i + 1].y, p.x, p.y);
	else
		vmse = vector_measure(sect->vert[0].x, sect->vert[0].y, p.x, p.y);
	if (vmfi < 1)
		return (1);
	else if (vmse < 1)
		return (2);
	else
		return (0);
}

int			check_horcoll(t_mapf *mapf)
{
	int		i;
	t_sector	*sect;

	i = 0;
	sect = &mapf->sectors[mapf->player.sect];
	while (i < sect->nbvert)
	{
		if (vm_check(mapf, i, sect))
		{
			if (check_near_edge(mapf, i, sect))
				return (1);
			if (sect->vert[i].neigh != -1)
			{
				if (check_port(mapf, i, sect) == 1)
				{
					slide_wall(mapf, i);
					mapf->player.coll++;
					return (1);
				}
				else
					return (0);
			}
			else
			{
					slide_wall(mapf, i);
					mapf->player.coll++;
					return (1);
			}
		}
		i++;
	}
	mapf->player.coll = 0;
	return (0);
}

void		move_chara(t_mapf *mapf, t_input *in)
{
	float	move_vec[2];
	float acc = 0.2f;
	float tmpx;
	float tmpy;

	move_vec[0] = 0.0f;
	move_vec[1] = 0.0f;
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
	tmpx = mapf->player.velo.x;
	tmpy = mapf->player.velo.y;
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
