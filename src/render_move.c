/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_move.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 09:32:13 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 13:01:05 by jfeve       ###    #+. /#+    ###.fr     */
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
		mapf->player.where.x += proj.x;
		mapf->player.where.y += proj.y;
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
			if (mapf->player.state == flying)
				mapf->player.add_z -= mapf->sectors[sect->vert[i].neigh].floor - mapf->sectors[mapf->player.sect].floor;
			mapf->player.sect = sect->vert[i].neigh;
			if (mapf->player.state != jumping && mapf->player.state != flying && mapf->player.state != crouching)
				mapf->player.state = falling;
			return (0);
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

int			check_horcoll(t_mapf *mapf)
{
	float	px = mapf->player.where.x;
	float	py = mapf->player.where.y;
	float	dx = mapf->player.velo.x;
	float	dy = mapf->player.velo.y;
	float	vmp;
	float	vmp2;
	float	vmw;
	int		i;
	t_sector	*sect;

	i = 0;
	sect = &mapf->sectors[mapf->player.sect];
	while (i < sect->nbvert)
	{
		if (i != sect->nbvert - 1)
		{
			vmw = vector_measure(sect->vert[i].x, sect->vert[i].y, sect->vert[i + 1].x, sect->vert[i + 1].y);
			vmp = vector_measure(sect->vert[i].x, sect->vert[i].y, px, py) +
				vector_measure(sect->vert[i + 1].x, sect->vert[i + 1].y, px, py);
			vmp2 = vector_measure(sect->vert[i].x, sect->vert[i].y, px + dx, py + dy ) +
				vector_measure(sect->vert[i + 1].x, sect->vert[i + 1].y, px + dx, py + dy);
		}
		else
		{
			vmw = vector_measure(sect->vert[i].x, sect->vert[i].y, sect->vert[0].x, sect->vert[0].y);
			vmp = vector_measure(sect->vert[i].x, sect->vert[i].y, px, py) +
				vector_measure(sect->vert[0].x, sect->vert[0].y, px, py);
			vmp2 = vector_measure(sect->vert[i].x, sect->vert[i].y, px + dx, py + dy ) +
				vector_measure(sect->vert[0].x, sect->vert[0].y, px + dx, py + dy);
		}
		if (vmp > vmp2 && vmp2 <= vmw + 0.1)
		{
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

int			check_interdxpx(t_float i, t_float p, t_float d)
{
	if (p.x > d.x)
	{
		if (p.y > d.y)
		{
			return (i.x <= p.x && i.x >= d.x && i.y <= p.y && i.y >= d.y);
		}
		else
		{
			return (i.x <= p.x && i.x >= d.x && i.y >= p.y && i.y <= d.y);
		}
	}
	else
	{
		if (p.y > d.y)
		{
			return (i.x >= p.x && i.x <= d.x && i.y <= p.y && i.y >= d.y);
		}
		else
		{
			return (i.x >= p.x && i.x <= d.x && i.y >= p.y && i.y <= d.y);
		}
	}
}

int			check_interab(t_float i, t_float a, t_float b)
{
	if (a.x > b.x)
	{
		if (a.y > b.y)
		{
			return (i.x <= a.x && i.x >= b.x && i.y <= a.y && i.y >= b.y);
		}
		else
		{
			return (i.x <= a.x && i.x >= b.x && i.y >= a.y && i.y <= b.y);
		}
	}
	else
	{
		if (a.y > b.y)
		{
			return (i.x >= a.x && i.x <= b.x && i.y <= a.y && i.y >= b.y);
		}
		else
		{
			return (i.x >= a.x && i.x <= b.x && i.y >= a.y && i.y <= b.y);
		}
	}
}

int			check_coll(t_mapf *mapf)
{
	float	px;
	float	py;
	float	dx;
	float	dy;
	t_sector *sec;
	int		i;
//	int		j;
	t_float	inter;

	i = 0;
	sec = &mapf->sectors[mapf->player.sect];
	px = mapf->player.where.x;
	py = mapf->player.where.y;
	dx = mapf->player.velo.x;
	dy = mapf->player.velo.y;
	dprintf(1, "\n\nvelox = %f\tveloy = %f\n", dx, dy);
	if (dx < 0.3)
		dx *= 6;
	if (dy < 0.3)
		dy *= 6;
	dprintf(1, "avelox = %f\taveloy = %f\n", dx, dy);
	dprintf(1, "-----------------------------------\n");
	while (i < sec->nbvert)
	{
		if (i != sec->nbvert - 1)
		{
			inter = f_intersect((t_float){px, py}, (t_float){px + dx, py + dy},
					(t_float){(float)sec->vert[i].x, (float)sec->vert[i].y},
					(t_float){(float)sec->vert[i + 1].x, (float)sec->vert[i + 1].y});
			dprintf(1, "inter [%f][%f] p [%f][%f] d [%f][%f] a [%d][%d] b [%d][%d]\n",
					inter.x, inter.y, px, py, px + dx, py + dy, sec->vert[i].x, sec->vert[i].y,
					sec->vert[i + 1].x, sec->vert[i + 1].y);
			if (check_interdxpx(inter, (t_float){px, py}, (t_float){px + dx, py + dy}))
			{
				if (check_interab(inter, (t_float){sec->vert[i].x, sec->vert[i].y},
							(t_float){sec->vert[i + 1].x, sec->vert[i + 1].y}))
				{
					dprintf(1, "intersect\t");
					slide_wall(mapf, i);
					return (0);
				}
			}
		}
		else
		{
			inter = f_intersect((t_float){px, py}, (t_float){px + dx, py + dy},
					(t_float){sec->vert[i].x, sec->vert[i].y},
					(t_float){sec->vert[0].x, sec->vert[0].y});
			if (check_interdxpx(inter, (t_float){px, py}, (t_float){px + dx, py + dy}))
			{
				if (check_interab(inter, (t_float){sec->vert[i].x, sec->vert[i].y},
							(t_float){sec->vert[0].x, sec->vert[0].y}))
				{
					dprintf(1, "intersect\t");
					slide_wall(mapf, i);
					return (0);
				}
			}
		}
		i++;
	}
	return (1);
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
		move_vec[0] += mapf->player.anglecos*0.2f;
		move_vec[1] += mapf->player.anglesin*0.2f;
	}
	if (in->key[SDL_SCANCODE_S])
	{
		move_vec[0] -= mapf->player.anglecos*0.2f;
		move_vec[1] -= mapf->player.anglesin*0.2f;
	}
	if (in->key[SDL_SCANCODE_A])
	{
		move_vec[0] += mapf->player.anglesin*0.2f;
		move_vec[1] -= mapf->player.anglecos*0.2f;
	}
	if (in->key[SDL_SCANCODE_D])
	{
		move_vec[0] -= mapf->player.anglesin*0.2f;
		move_vec[1] += mapf->player.anglecos*0.2f;
	}
	tmpx = mapf->player.velo.x;
	tmpy = mapf->player.velo.y;
	mapf->player.velo.x = mapf->player.velo.x * (1 - acc) + move_vec[0]
	* acc;
	mapf->player.velo.y = mapf->player.velo.y * (1 - acc) + move_vec[1]
	* acc;
	if (check_horcoll(mapf) == 0)
	{
//	if (check_coll(mapf) == 1)
//	{
		mapf->player.where.x += mapf->player.velo.x;
		mapf->player.where.y += mapf->player.velo.y;
	}
//	}
}

