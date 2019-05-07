/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths_5.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 20:21:59 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 20:22:27 by flombard    ###    #+. /#+    ###.fr     */
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
