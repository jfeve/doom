/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_draw_norm.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 17:47:33 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 21:45:40 by jfeve       ###    #+. /#+    ###.fr     */
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
