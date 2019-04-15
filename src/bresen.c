/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bresen.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:26:28 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 19:38:20 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static	void		do_5(t_bresen *brs)
{
	if (brs->dy > 0)
	{
		while (brs->a->y != brs->b->y)
		{
			if (brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != RED &&
						brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != GREEN &&
						brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != PURPLE)
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] = brs->b->col;
			brs->a->y++;
		}
	}
	else
	{
		while (brs->a->y != brs->b->y)
		{
			if (brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != RED &&
						brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != GREEN &&
						brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != PURPLE)
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] = brs->b->col;
			brs->a->y--;
		}
	}
}

static	void		do_6(t_bresen *brs)
{
	while (brs->a->x != brs->b->x)
	{
		if (brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != RED &&
					brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != GREEN &&
					brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != PURPLE)
			brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] = brs->b->col;
		brs->a->x++;
	}
}

static	void		do_global(t_bresen *brs)
{
	if (brs->dy < 0)
	{
		if (brs->dx >= -1 * brs->dy)
			do_1(brs);
		else
			do_2(brs);
	}
	else if (brs->dy > 0)
	{
		if (brs->dx >= brs->dy)
			do_3(brs);
		else
			do_4(brs);
	}
	else
		do_6(brs);
}

void			bresen(t_lis a, t_lis b, t_sdl *sdl)
{
	t_bresen	brs;

	brs.a = &a;
	brs.b = &b;
	brs.sdl = sdl;
	brs.a->col = brs.b->col;
	brs.dx = brs.b->x - brs.a->x;
	brs.dy = brs.b->y - brs.a->y;
	if (brs.dx > 0)
		do_global(&brs);
	else if (brs.dx == 0)
		do_5(&brs);
	else
		bresen(b, a, sdl);
}
