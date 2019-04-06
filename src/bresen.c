/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bresen.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:26:28 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 17:20:18 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			bresen(t_lis a, t_lis b, t_sdl *sdl)
{
	int dx;
	int dy;
	int e;

	a.col = b.col;
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (dx > 0)
	{
		if (dy < 0)
		{
			if (dx >= -1 * dy)
			{
				e = dx;
				dx *= 2;
				dy *= 2;
				while (a.x != b.x)
				{
					sdl->pix[a.y * WIN_W + a.x] = b.col;
					e += dy;
					if (e < 0)
					{
						a.y -=1;
						e += dx;
					}
					a.x +=1;
				}
			}
			else
			{
				e = dy;
				dx *= 2;
				dy *= 2;
				while (a.y != b.y)
				{
					sdl->pix[a.y * WIN_W + a.x] = b.col;
					e += dx;
					if (e > 0)
					{
						a.x +=1;
						e += dy;
					}
					a.y -=1;
				}
			}
		}
		else if (dy > 0)
		{
			if (dx >= dy)
			{
				e = dx;
				dx *= 2;
				dy *= 2;
				while (a.x != b.x)
				{
					sdl->pix[a.y * WIN_W + a.x] = b.col;
					e -= dy;
					if (e < 0)
					{
						a.y +=1;
						e += dx;
					}
					a.x +=1;
				}
			}
			else
			{
				e = dy;
				dx *= 2;
				dy *= 2;
				while (a.y != b.y)
				{
					sdl->pix[a.y * WIN_W + a.x] = b.col;
					e -= dx;
					if (e < 0)
					{
						a.x +=1;
						e += dy;
					}
					a.y +=1;
				}
			}
		}
		else
		{
			while (a.x != b.x)
			{
				sdl->pix[a.y * WIN_W + a.x] = b.col;
				a.x++;
			}
		}
	}
	else if (dx == 0)
	{
		if (dy > 0)
		{
			while (a.y != b.y)
			{
				sdl->pix[a.y * WIN_W + a.x] = b.col;
				a.y++;
			}
		}
		else
		{
			while (a.y != b.y)
			{
				sdl->pix[a.y * WIN_W + a.x] = b.col;
				a.y--;
			}
		}
	}
	else
		bresen(b, a, sdl);
}
