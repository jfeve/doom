/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_draw_init.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 16:20:20 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 16:26:06 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

t_float		create_float(float a, float b)
{
	t_float	x;

	x.x = a;
	x.y = b;
	return (x);
}

void		init_v1v2(t_ren *ren, int s, t_sector *sect, t_mapf *mapf)
{
	if (s == sect->nbvert - 1)
	{
		ren->v1.x = sect->vert[s].x - mapf->player.where.x;
		ren->v1.y = sect->vert[s].y - mapf->player.where.y;
		ren->v2.x = sect->vert[0].x - mapf->player.where.x;
		ren->v2.y = sect->vert[0].y - mapf->player.where.y;
	}
	else
	{
		ren->v1.x = sect->vert[s].x - mapf->player.where.x;
		ren->v1.y = sect->vert[s].y - mapf->player.where.y;
		ren->v2.x = sect->vert[s + 1].x - mapf->player.where.x;
		ren->v2.y = sect->vert[s + 1].y - mapf->player.where.y;
	}
}

void		init_ren(t_mapf *mapf, t_ren *ren)
{
	int		i;

	i = 0;
	ren->head = ren->queue;
	ren->tail = ren->queue;
	while (i < RWIN_W)
		ren->ybot[i++] = RWIN_H - 1;
	i = 0;
	while (i < RWIN_W)
		ren->ytop[i++] = 0;
	ren->head->sect = mapf->player.sect;
	ren->head->sx1 = 0;
	ren->head->sx2 = RWIN_W - 1;
	if (++ren->head == ren->queue + MAXQ)
		ren->head = ren->queue;
	ren->pcos = mapf->player.anglecos;
	ren->psin = mapf->player.anglesin;
}
