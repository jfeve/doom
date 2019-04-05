/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bresen2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/14 17:42:09 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 14:04:47 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void		ft_dx_sup_zero(t_point a, t_point b, t_sdl *sdl)
{
	int dy;
	int dx;
	int e;

	dy = (b.y - a.y) * 2;
	dx = (b.x - a.x) * 2;
	e = dx / 2;
	while (a.x != b.x)
	{
		ft_pixel(a.x, a.y, sdl);
		if ((e -= fabs((double)dy)) < 0)
		{
			if (dy > 0)
				a.y++;
			else if (dy < 0)
				a.y--;
			e += dx;
		}
		a.x++;
	}
}

static void		ft_dx_inf_zero(t_point a, t_point b, t_sdl *sdl)
{
	int dy;
	int dx;
	int e;

	dy = (b.y - a.y) * 2;
	dx = (b.x - a.x) * 2;
	e = dx / 2;
	while (a.x != b.x)
	{
		ft_pixel(a.x, a.y, sdl);
		if ((e += fabs((double)dy)) < 0)
		{
			if (dy > 0)
				a.y++;
			else if (dy < 0)
				a.y--;
			e += dx;
		}
		a.x--;
	}
}

static void		ft_dy_supzero(t_point a, t_point b, int e, t_sdl *sdl)
{
	int dy;
	int dx;

	dx = (b.x - a.x) * 2;
	dy = (b.y - a.y) * 2;
	while (a.y != b.y)
	{
		ft_pixel(a.x, a.y, sdl);
		if (((e -= fabs((double)dx)) < 0) || (e == 0 && dx < 0))
		{
			if (dx > 0)
				a.x++;
			else if (dx < 0)
				a.x--;
			e += dy;
		}
		a.y++;
	}
}

static void		ft_dy_infzero(t_point a, t_point b, int e, t_sdl *sdl)
{
	int dy;
	int dx;

	dx = (b.x - a.x) * 2;
	dy = (b.y - a.y) * 2;
	while (a.y != b.y)
	{
		ft_pixel(a.x, a.y, sdl);
		if (((e += fabs((double)dx)) < 0) || (e == 0 && dx < 0))
		{
			if (dx > 0)
				a.x++;
			else if (dx < 0)
				a.x--;
			e += dy;
		}
		a.y--;
	}
}

void			ft_bresen(t_point a, t_point b, t_sdl *sdl)
{
	int dx;
	int dy;
	int e;

	dx = (b.x - a.x) * 2;
	dy = (b.y - a.y) * 2;
	if (dx == 0)
		ft_dx_zero(a.x, a.y, b.y, sdl);
	else if (dy == 0)
		ft_dy_zero(a.x, a.y, b.x, sdl);
	else if (fabs((double)dx / 2) >= fabs((double)dy / 2))
	{
		if (dx > 0)
			ft_dx_sup_zero(a, b, sdl);
		else if (dx < 0)
			ft_dx_inf_zero(a, b, sdl);
	}
	else if (fabs((double)dx / 2) < fabs((double)dy / 2))
	{
		e = ft_value_e(dx, dy);
		if (dy > 0)
			ft_dy_supzero(a, b, e, sdl);
		else if (dy < 0)
			ft_dy_infzero(a, b, e, sdl);
	}
}
