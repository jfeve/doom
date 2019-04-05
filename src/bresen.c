/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bresen.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 16:37:06 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 14:03:12 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void	ft_pixel(int x, int y, t_sdl *sdl)
{
	if (sdl->color != 0)
		sdl->pix[y * WIN_W + x] = sdl->color;
	else
		sdl->pix[y * WIN_W + x] = WHITE;
}

void	ft_dy_zero(int x1, int y1, int x2, t_sdl *sdl)
{
	int dx;

	dx = (x2 - x1) * 2;
	while (x1 != x2)
	{
		ft_pixel(x1, y1, sdl);
		if (dx > 0)
			x1++;
		else if (dx < 0)
			x1--;
	}
}

void	ft_dx_zero(int x1, int y1, int y2, t_sdl *sdl)
{
	int dy;

	dy = (y2 - y1) * 2;
	while (y1 != y2)
	{
		ft_pixel(x1, y1, sdl);
		if (dy > 0)
			y1++;
		else if (dy < 0)
			y1--;
	}
}

int		ft_value_e(int dx, int dy)
{
	int e;

	if (dy > 0 && dx < 0)
		e = dx;
	else
		e = dy;
	return (e);
}
