/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_draw_get.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 18:10:33 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:34:54 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void		get_ycy(t_ren *ren, int x)
{
	ren->xx.tx = ((ren->u.x * (ren->x2 - x) * ren->t2.y) + (ren->u.y *
		(x - ren->x1) * ren->t1.y)) / ((ren->x2 - x) * ren->t2.y +
		(x - ren->x1) * ren->t1.y);
	ren->xx.ya = ((x - ren->x1) * (ren->y2.x - ren->y1.x)) /
		(ren->x2 - ren->x1) + ren->y1.x;
	ren->xx.yb = ((x - ren->x1) * (ren->y2.y - ren->y1.y)) /
		(ren->x2 - ren->x1) + ren->y1.y;
	ren->xx.cya = clamp(ren->xx.ya, ren->ytop[x], ren->ybot[x]);
	ren->xx.cyb = clamp(ren->xx.yb, ren->ytop[x], ren->ybot[x]);
}

void		get_t1t2(t_ren *ren)
{
	ren->t1.x = ren->v1.x * ren->psin - ren->v1.y * ren->pcos;
	ren->t1.y = ren->v1.x * ren->pcos + ren->v1.y * ren->psin;
	ren->t2.x = ren->v2.x * ren->psin - ren->v2.y * ren->pcos;
	ren->t2.y = ren->v2.x * ren->pcos + ren->v2.y * ren->psin;
	ren->u = (t_point){0, 199};
}

int			get_x(t_float t)
{
	float	xscale;
	int		x;

	xscale = HFOV / t.y;
	x = RWIN_W / 2 - (int)(t.x * xscale);
	return (x);
}

void		computey(t_ren *ren, t_mapf *mapf, float ys1, float ys2)
{
	ren->y1.x = RWIN_H / 2 - (yaw(ren->yceil, ren->t1.y, mapf->player.yaw)
			* ys1);
	ren->y1.y = RWIN_H / 2 - (yaw(ren->yfloor, ren->t1.y, mapf->player.yaw)
			* ys1);
	ren->y2.x = RWIN_H / 2 - (yaw(ren->yceil, ren->t2.y, mapf->player.yaw)
			* ys2);
	ren->y2.y = RWIN_H / 2 - (yaw(ren->yfloor, ren->t2.y, mapf->player.yaw)
			* ys2);
}

void		get_yny(t_ren *ren, t_mapf *mapf, t_sector *sect, int s)
{
	float	ys1;
	float	ys2;
	float	nyceil;
	float	nyfloor;

	ys1 = VFOV / ren->t1.y;
	ys2 = VFOV / ren->t2.y;
	ren->neigh = sect->vert[s].neigh;
	nyceil = 0;
	nyfloor = 0;
	ren->yceil = sect->ceil - mapf->player.where.z;
	ren->yfloor = sect->floor - mapf->player.where.z;
	if (ren->neigh >= 0)
	{
		nyceil = mapf->sectors[ren->neigh].ceil - mapf->player.where.z;
		nyfloor = mapf->sectors[ren->neigh].floor - mapf->player.where.z;
	}
	computey(ren, mapf, ys1, ys2);
	ren->ny1.x = RWIN_H / 2 - ((nyceil + ren->t1.y * mapf->player.yaw) * ys1);
	ren->ny1.y = RWIN_H / 2 - ((nyfloor + ren->t1.y * mapf->player.yaw) * ys1);
	ren->ny2.x = RWIN_H / 2 - ((nyceil + ren->t2.y * mapf->player.yaw) * ys2);
	ren->ny2.y = RWIN_H / 2 - ((nyfloor + ren->t2.y * mapf->player.yaw) * ys2);
}
