/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths_3.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 16:42:47 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 11:43:16 by jfeve       ###    #+. /#+    ###.fr     */
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
	return (overlap((t_point){a.x, b.x}, (t_point){c.x, d.x}) &&
			overlap((t_point){a.y, b.y}, (t_point){c.y, d.y}));
}

int			f_intersectbox(t_float a, t_float b, t_float c, t_float d)
{
	return (f_overlap((t_float){a.x, b.x}, (t_float){c.x, d.x}) &&
			f_overlap((t_float){a.y, b.y}, (t_float){c.y, d.y}));
}
