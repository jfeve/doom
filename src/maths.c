/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 13:22:54 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 15:48:53 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				min(int a, int b)
{
	return ((a < b) ? a : b);
}

int				max(int a, int b)
{
	return ((a > b) ? a : b);
}

float			f_min(float a, float b)
{
	return ((a < b) ? a : b);
}

float			f_max(float a, float b)
{
	return ((a > b) ? a : b);
}

t_lis			mult_unit(t_lis vert)
{
	t_lis	a;

	a.x = vert.x * UNIT;
	a.y = vert.y * UNIT;
	a.col = vert.col;
	return (a);
}

float			arr_float(float x)
{
	if ((int)x % UNIT >= UNIT / 2)
		x += UNIT / 2 + 1;
	return (x / UNIT);
}

int				arr(int x)
{
	if (x % UNIT >= UNIT / 2)
		x += UNIT / 2 + 1;
	return (x / UNIT);
}
