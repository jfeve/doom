/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths_2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 16:28:51 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 16:40:20 by jfeve       ###    #+. /#+    ###.fr     */
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

int			vxs(t_point a, t_point b)
{
	return (a.x * b.y - a.y * b.x);
}

float		f_vxs(t_float a, t_float b)
{
	return (a.x * b.y - a.y * b.x);
}
