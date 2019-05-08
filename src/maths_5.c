/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths_5.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 20:21:59 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:30:50 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

float	arr_float(float x)
{
	if ((int)x % UNIT >= UNIT / 2)
		x += UNIT / 2 + 1;
	return (x / UNIT);
}

int		arr(int x)
{
	if (x % UNIT >= UNIT / 2)
		x += UNIT / 2 + 1;
	return (x / UNIT);
}

float		vector_measure(float x1, float y1, float x2, float y2)
{
	float dx;
	float dy;
	float res;

	dx = x2 - x1;
	dy = y2 - y1;
	res = sqrtf(dx * dx + dy * dy);
	return (res);
}
