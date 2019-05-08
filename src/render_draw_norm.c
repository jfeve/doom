/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_draw_norm.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 17:47:33 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:12:07 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void		fill_head(t_ren *ren, int beginx, int endx)
{
	if (ren->neigh >= 0 && endx >= beginx &&
			(ren->head + MAXQ + 1 - ren->tail) % MAXQ)
	{
		ren->head->sect = ren->neigh;
		ren->head->sx1 = beginx;
		ren->head->sx2 = endx;
		if (++ren->head == ren->queue + MAXQ)
			ren->head = ren->queue;
	}
}

void		fill_rends(t_mapf *mapf, t_queue now)
{
	mapf->rend_s[mapf->nbrend_s].id = now.sect;
	mapf->rend_s[mapf->nbrend_s].beginx = now.sx1;
	mapf->rend_s[mapf->nbrend_s].endx = now.sx2;
	mapf->nbrend_s++;
}
