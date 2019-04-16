/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 13:22:54 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 15:28:32 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

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
