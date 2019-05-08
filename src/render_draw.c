/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_draw.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 09:36:31 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:55:00 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			draw_neigh(t_mapf *mapf, t_ren *ren, int s, int x)
{
	t_sector	*sect;

	sect = &mapf->sectors[ren->now.sect];
	if (ren->neigh >= 0)
	{
		ren->xx.nya = (x - ren->x1) * (ren->ny2.x - ren->ny1.x)
			/ (ren->x2 - ren->x1) + ren->ny1.x;
		ren->xx.cnya = clamp(ren->xx.nya, ren->ytop[x], ren->ybot[x]);
		ren->xx.nyb = (x - ren->x1) * (ren->ny2.y - ren->ny1.y)
			/ (ren->x2 - ren->x1)
			+ ren->ny1.y;
		ren->xx.cnyb = clamp(ren->xx.nyb, ren->ytop[x], ren->ybot[x]);
		draw_text(mapf, ren, (t_quad){x, s, ren->xx.ya, ren->xx.nya - 1}, sect);
		ren->ytop[x] = clamp(max(ren->xx.cya, ren->xx.cnya),
				ren->ytop[x], RWIN_H - 1);
		draw_text(mapf, ren, (t_quad){x, s, ren->xx.nyb + 1, ren->xx.yb}, sect);
		ren->ybot[x] = clamp(min(ren->xx.cyb, ren->xx.cnyb), 0, ren->ybot[x]);
	}
	else
		draw_text(mapf, ren, (t_quad){x, s, ren->xx.ya, ren->xx.yb}, sect);
}

void			draw_pix(t_mapf *mapf, t_ren *ren, int s, t_sector *sect)
{
	int			beginx;
	int			endx;
	int			x;

	ren->x1 = get_x(ren->t1);
	ren->x2 = get_x(ren->t2);
	if (ren->x1 >= ren->x2 || ren->x2 < ren->now.sx1 || ren->x1 > ren->now.sx2)
		return ;
	get_yny(ren, mapf, sect, s);
	beginx = max(ren->x1, ren->now.sx1);
	endx = min(ren->x2, ren->now.sx2);
	x = beginx;
	while (x <= endx)
	{
		if (ren->x2 - ren->x1 == 0)
			break ;
		get_ycy(ren, x);
		draw(mapf, (t_point){x, DARK_GREY}, (t_point){ren->ytop[x],
				ren->xx.cya - 1}, sect);
		draw(mapf, (t_point){x, BROWN}, (t_point){ren->xx.cyb + 1,
				ren->ybot[x]}, sect);
		draw_neigh(mapf, ren, s, x);
		x++;
	}
	fill_head(ren, beginx, endx);
}

void			draw_vector(t_ren *ren, int s, t_sector *sect, t_mapf *mapf)
{
	init_v1v2(ren, s, sect, mapf);
	get_t1t2(ren);
	if (ren->t1.y < 0 && ren->t2.y < 0)
		return ;
	clip_t1t2(ren);
	draw_pix(mapf, ren, s, sect);
}

void			draw_sect(t_mapf *mapf, t_ren *ren, int *rendersect)
{
	t_sector	*sect;
	int			s;

	s = 0;
	ren->now = *ren->tail;
	if (++ren->tail == ren->queue + MAXQ)
		ren->tail = ren->queue;
	if ((rendersect[ren->now.sect] & 0x21))
		return ;
	rendersect[ren->now.sect]++;
	sect = &mapf->sectors[ren->now.sect];
	fill_rends(mapf, ren->now);
	while (s < sect->nbvert)
	{
		draw_vector(ren, s, sect, mapf);
		s++;
	}
}

void			fill_pix(t_mapf *mapf)
{
	t_ren		ren;
	int			rendersect[mapf->nbsect];
	int			i;

	i = 0;
	ft_bzero(&ren, sizeof(t_ren));
	init_ren(mapf, &ren);
	while (i < mapf->nbsect)
		rendersect[i++] = 0;
	while (ren.head != ren.tail)
	{
		draw_sect(mapf, &ren, rendersect);
		++rendersect[ren.now.sect];
	}
}
