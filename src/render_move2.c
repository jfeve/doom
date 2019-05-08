/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_move2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 15:45:51 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 17:11:12 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static int	check_port2(t_mapf *mapf, t_sector *sect, int i)
{
	if (mapf->player.where.z - mapf->player.eye + KNEE
	> mapf->sectors[sect->vert[i].neigh].floor && mapf->player.where.z
	< mapf->sectors[sect->vert[i].neigh].ceil)
	{
		if (mapf->player.state != jumping && mapf->player.state != flying
		&& mapf->player.state != crouching)
			mapf->player.state = falling;
		if (mapf->player.state == flying || mapf->player.state == jumping
		|| mapf->player.state == falling)
			mapf->player.add_z -= mapf->sectors[sect->vert[i].neigh].floor
			- mapf->sectors[mapf->player.sect].floor;
		mapf->sectors[mapf->player.sect].lum = 0;
		mapf->player.sect = sect->vert[i].neigh;
		mapf->sectors[mapf->player.sect].lum = 1;
		return (0);
	}
	return (1);
}

static void	init_pts(t_float *p, t_float *d, t_mapf *mapf)
{
	p->x = mapf->player.where.x;
	p->y = mapf->player.where.y;
	d->x = mapf->player.velo.x;
	d->y = mapf->player.velo.y;
}

static void	norm(t_sector *sect, int i, t_cport *c)
{
	if (i != sect->nbvert - 1)
	{
		c->ps = f_pointside((t_float){c->p.x, c->p.y},
		(t_float){sect->vert[i].x, sect->vert[i].y},
		(t_float){sect->vert[i + 1].x, sect->vert[i + 1].y});
		c->ps2 = f_pointside((t_float){c->p.x + c->d.x, c->p.y + c->d.y},
		(t_float){sect->vert[i].x, sect->vert[i].y},
		(t_float){sect->vert[i + 1].x, sect->vert[i + 1].y});
	}
	else
	{
		c->ps = f_pointside((t_float){c->p.x, c->p.y},
		(t_float){sect->vert[i].x, sect->vert[i].y},
		(t_float){sect->vert[0].x, sect->vert[0].y});
		c->ps2 = f_pointside((t_float){c->p.x + c->d.x, c->p.y + c->d.y},
		(t_float){sect->vert[i].x, sect->vert[i].y},
		(t_float){sect->vert[0].x, sect->vert[0].y});
	}
}

int			check_port(t_mapf *mapf, int i, t_sector *sect)
{
	t_cport	c;

	init_pts(&c.p, &c.d, mapf);
	norm(sect, i, &c);
	if ((c.ps >= fabs(c.d.x * 4) && c.ps2 <= fabs(c.d.x * 4)) || (c.ps
	<= fabs(c.d.x * 4) && c.ps2 >= fabs(c.d.x * 4)))
		if (check_port2(mapf, sect, i) == 1)
			return (1);
	return (0);
}
