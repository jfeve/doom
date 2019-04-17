/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths_3.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 16:42:47 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 19:05:12 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int			overlap(t_point a, t_point b)
{
	return (min(a.x, a.y) <= max(b.x, b.y) && min(b.x, b.y) <= max(a.x, a.y));
}

int			f_overlap(t_float a, t_float b)
{
	return (f_min(a.x, a.y) <= f_max(b.x, b.y) && f_min(b.x, b.y) <=
			f_max(a.x, a.y));
}

int			intersectbox(t_point a, t_point b, t_point c, t_point d)
{
	t_point	x;
	t_point	y;
	t_point	w;
	t_point	z;

	x.x = a.x;
	x.y = b.x;
	y.x = c.x;
	y.y = d.x;
	w.x = a.y;
	w.y = b.y;
	z.x = c.y;
	z.y = d.y;
	return (overlap(x, y) && overlap(w, z));
}

int			f_intersectbox(t_float a, t_float b, t_float c, t_float d)
{
	t_float	x;
	t_float	y;
	t_float	w;
	t_float	z;

	x.x = a.x;
	x.y = b.x;
	y.x = c.x;
	y.y = d.x;
	w.x = a.y;
	w.y = b.y;
	z.x = c.y;
	z.y = d.y;
	return (f_overlap(x, y) && f_overlap(w, z));
}
