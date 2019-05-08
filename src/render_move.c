/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_move.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 09:32:13 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:02:19 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

t_float		vmp_compute(t_sector *sect, t_float p, t_float d, t_point i)
{
	t_float	vmp;

	vmp.x = vector_measure(sect->vert[i.x].x, sect->vert[i.x].y, p.x, p.y)
	+ vector_measure(sect->vert[i.y].x, sect->vert[i.y].y, p.x, p.y);
	vmp.y = vector_measure(sect->vert[i.x].x, sect->vert[i.x].y, p.x + d.x,
	p.y + d.y) + vector_measure(sect->vert[i.y].x, sect->vert[i.y].y,
	p.x + d.x, p.y + d.y);
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
		vmw = vector_measure(sect->vert[i].x, sect->vert[i].y,
		sect->vert[i + 1].x, sect->vert[i + 1].y);
		vmp = vmp_compute(sect, p, d, (t_point){i, i + 1});
	}
	else
	{
		vmw = vector_measure(sect->vert[i].x, sect->vert[i].y, sect->vert[0].x,
		sect->vert[0].y);
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
		vmse = vector_measure(sect->vert[i + 1].x, sect->vert[i + 1].y,
		p.x, p.y);
	else
		vmse = vector_measure(sect->vert[0].x, sect->vert[0].y, p.x, p.y);
	if (vmfi < 1)
		return (1);
	else if (vmse < 1)
		return (2);
	else
		return (0);
}

static int	norm(t_mapf *mapf, int i, t_sector *sect)
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

int			check_horcoll(t_mapf *mapf)
{
	int			i;
	t_sector	*sect;

	i = 0;
	sect = &mapf->sectors[mapf->player.sect];
	while (i < sect->nbvert)
	{
		if (vm_check(mapf, i, sect))
		{
			if (norm(mapf, i, sect))
				return (1);
			else
				return (0);
		}
		i++;
	}
	mapf->player.coll = 0;
	return (0);
}
