/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bresen_bis.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hironichu <hironichu@student.le-101.fr>    +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 19:13:08 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 18:07:25 by hironichu   ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			do_1(t_bresen *brs)
{
	int		e;

	e = brs->dx;
	brs->dx *= 2;
	brs->dy *= 2;
	while (brs->a->x != brs->b->x)
	{
		if (brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != RED &&
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != GREEN &&
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != PURPLE)
			brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] = brs->b->col;
		e += brs->dy;
		if (e < 0)
		{
			brs->a->y -= 1;
			e += brs->dx;
		}
		brs->a->x += 1;
	}
}

void			do_2(t_bresen *brs)
{
	int		e;

	e = brs->dy;
	brs->dx *= 2;
	brs->dy *= 2;
	while (brs->a->y != brs->b->y)
	{
		if (brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != RED &&
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != GREEN &&
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != PURPLE)
			brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] = brs->b->col;
		e += brs->dx;
		if (e > 0)
		{
			brs->a->x += 1;
			e += brs->dy;
		}
		brs->a->y -= 1;
	}
}

void			do_3(t_bresen *brs)
{
	int		e;

	e = brs->dx;
	brs->dx *= 2;
	brs->dy *= 2;
	while (brs->a->x != brs->b->x)
	{
		if (brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != RED &&
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != GREEN &&
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != PURPLE)
			brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] = brs->b->col;
		e -= brs->dy;
		if (e < 0)
		{
			brs->a->y += 1;
			e += brs->dx;
		}
		brs->a->x += 1;
	}
}

void			do_4(t_bresen *brs)
{
	int		e;

	e = brs->dy;
	brs->dx *= 2;
	brs->dy *= 2;
	while (brs->a->y != brs->b->y)
	{
		if (brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != RED &&
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != GREEN &&
				brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] != PURPLE)
			brs->sdl->pix[brs->a->y * WIN_W + brs->a->x] = brs->b->col;
		e -= brs->dx;
		if (e < 0)
		{
			brs->a->x += 1;
			e += brs->dy;
		}
		brs->a->y += 1;
	}
}
