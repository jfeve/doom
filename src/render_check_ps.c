/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_check_ps.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 18:31:16 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:51:09 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static int	norm(t_mapf *mapf, t_cps *c)
{
	c->cpt++;
	if (c->sec->vert[c->i].neigh != -1)
	{
		if (mapf->player.where.z - mapf->player.eye + KNEE
		> mapf->sectors[c->sec->vert[c->i].neigh].floor
		&& mapf->player.where.z
		< mapf->sectors[c->sec->vert[c->i].neigh].ceil)
		{
			if (mapf->player.state != jumping && mapf->player.state
			!= flying && mapf->player.state != crouching)
				mapf->player.state = falling;
			mapf->sectors[mapf->player.sect].lum = 0;
			mapf->player.sect = c->sec->vert[c->i].neigh;
			mapf->sectors[mapf->player.sect].lum = 1;
			if (mapf->player.state != jumping && mapf->player.state
			!= flying)
				mapf->player.state = falling;
			return (0);
		}
	}
	return (1);
}

static int	norm2(t_mapf *mapf, t_cps *c)
{
	if (c->sec->vert[c->i].neigh == -1)
	{
		c->i++;
		mapf->player.where = (t_xyz){mapf->old.x, mapf->old.y,
		mapf->old.z};
	}
	else
	{
		if (mapf->player.where.z - mapf->player.eye + KNEE
		> mapf->sectors[c->sec->vert[c->i].neigh].floor && mapf->player.where.z
		< mapf->sectors[c->sec->vert[c->i].neigh].ceil)
		{
			if (mapf->player.state != jumping && mapf->player.state
			!= flying && mapf->player.state != crouching)
				mapf->player.state = falling;
			mapf->sectors[mapf->player.sect].lum = 0;
			mapf->player.sect = c->sec->vert[c->i].neigh;
			mapf->sectors[mapf->player.sect].lum = 1;
			if (mapf->player.state != jumping && mapf->player.state
			!= flying)
				mapf->player.state = falling;
			return (0);
		}
	}
	return (1);
}

static int	norm3(t_mapf *mapf, t_cps *c)
{
	if (c->i != c->sec->nbvert - 1)
	{
		c->ps = f_pointside((t_float){mapf->player.where.x,
		mapf->player.where.y}, (t_float){c->sec->vert[c->i].x,
		c->sec->vert[c->i].y}, (t_float){c->sec->vert[c->i + 1].x,
		c->sec->vert[c->i + 1].y});
		if (c->ps < 0)
			if (!norm(mapf, c))
				return (0);
	}
	else
	{
		c->ps = f_pointside((t_float){mapf->player.where.x,
		mapf->player.where.y}, (t_float){c->sec->vert[c->i].x,
		c->sec->vert[c->i].y}, (t_float){c->sec->vert[0].x, c->sec->vert[0].y});
		if (c->ps < 0)
			if (!norm2(mapf, c))
				return (0);
	}
	return (1);
}

int			check_ps(t_mapf *mapf)
{
	t_cps	c;

	c.i = 0;
	c.cpt = 0;
	c.sec = &mapf->sectors[mapf->player.sect];
	while (c.i < c.sec->nbvert)
	{
		if (!norm3(mapf, &c))
			return (0);
		(c.i)++;
	}
	if (c.cpt)
		mapf->player.where = (t_xyz){mapf->old.x, mapf->old.y, mapf->old.z};
	return (1);
}
