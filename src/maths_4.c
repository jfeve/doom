/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths_4.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 17:34:38 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 21:20:41 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				pointside(t_point p, t_point a, t_point b)
{
	return (vxs(b.x - a.x, b.y - a.y, p.x - a.x, p.y - a.y));
}

float			f_pointside(t_float p, t_float a, t_float b)
{
	return (vxs(b.x - a.x, b.y - a.y, p.x - a.x, p.y - a.y));
}

t_float			f_intersect(t_float a, t_float b, t_float c, t_float d)
{
	t_float		ret;

	ret.x = (f_vxs(f_vxs(a.x, a.y, b.x, b.y), a.x - b.x,
			f_vxs(c.x, c.y, d.x, d.y), c.x - d.x) /
			f_vxs(a.x - b.x, a.x - b.y, c.x - d.x, c.y - d.y));
	ret.y = (f_vxs(f_vxs(a.x, a.y, b.x, b.y), a.y - b.y,
			f_vxs(c.x, c.y, d.x, d.y), c.y - d.y) /
			f_vxs(a.x - b.x, a.x - b.y, c.x - d.x, c.y - d.y));
	return (ret);
}

//int				yaw(int y, int z)
//{
//	return (y + z * player.yaw);
//}
