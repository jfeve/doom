/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 13:22:54 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 20:22:36 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int		min(int a, int b)
{
	return ((a < b) ? a : b);
}

int		max(int a, int b)
{
	return ((a > b) ? a : b);
}

float	f_min(float a, float b)
{
	return ((a < b) ? a : b);
}

float	f_max(float a, float b)
{
	return ((a > b) ? a : b);
}

t_lis	mult_unit(t_lis vert)
{
	t_lis	a;

	a.x = vert.x * UNIT;
	a.y = vert.y * UNIT;
	a.col = vert.col;
	return (a);
}
