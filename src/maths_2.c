/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths_2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 16:28:51 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 22:29:06 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int			clamp(int a, int mi, int ma)
{
	return (min(max(a, mi), ma));
}

float		f_clamp(float a, float mi, float ma)
{
	return (f_min(f_max(a, mi), ma));
}

int			vxs(int ax, int ay, int bx, int by)
{
	return (ax * by - ay * bx);
}

float		f_vxs(float ax, float ay, float bx, float by)
{
	return ((ax * by) - (ay * bx));
}
