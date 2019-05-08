/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_draw_clip.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 16:23:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:13:40 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

t_float		get_nfinter(t_ren *ren, t_float near, t_float far, int flag)
{
	t_float	a;
	t_float	b;
	t_float	c;
	t_float	d;

	a = (t_float){ren->t1.x, ren->t1.y};
	b = (t_float){ren->t2.x, ren->t2.y};
	if (flag == 0)
	{
		c = (t_float){-near.y, near.x};
		d = (t_float){-far.y, far.x};
	}
	else
	{
		c = (t_float){near.y, near.x};
		d = (t_float){far.y, far.x};
	}
	return (f_intersect(a, b, c, d));
}

void		clip_u(t_ren *ren)
{
	if (fabs(ren->t2.x - ren->t1.x) > fabs(ren->t2.y - ren->t1.y))
	{
		ren->u.x = (ren->t1.x - ren->org1.x) * 199 / (ren->org2.x -
				ren->org1.x);
		ren->u.y = (ren->t2.x - ren->org1.x) * 199 / (ren->org2.x -
				ren->org1.x);
	}
	else
	{
		ren->u.x = (ren->t1.y - ren->org1.y) * 199 / (ren->org2.y -
				ren->org1.y);
		ren->u.y = (ren->t2.y - ren->org1.y) * 199 / (ren->org2.y -
				ren->org1.y);
	}
}

void		clip2_t1t2(t_ren *ren, t_float i1, t_float i2, t_float near)
{
	if (ren->t1.y < near.x)
	{
		if (i1.y > 0)
			ren->t1 = (t_float){i1.x, i1.y};
		else
			ren->t1 = (t_float){i2.x, i2.y};
	}
	if (ren->t2.y < near.x)
	{
		if (i1.y > 0)
			ren->t2 = (t_float){i1.x, i1.y};
		else
			ren->t2 = (t_float){i2.x, i2.y};
	}
}

void		clip_t1t2(t_ren *ren)
{
	t_float	near;
	t_float	far;
	t_float	i1;
	t_float	i2;

	if (ren->t1.y <= 0 || ren->t2.y <= 0)
	{
		near = (t_float){0.0001f, 0.00001f};
		far = (t_float){5.f, 20.f};
		i1 = get_nfinter(ren, near, far, 0);
		i2 = get_nfinter(ren, near, far, 1);
		ren->org1 = (t_float){ren->t1.x, ren->t1.y};
		ren->org2 = (t_float){ren->t2.x, ren->t2.y};
		clip2_t1t2(ren, i1, i2, near);
		clip_u(ren);
	}
}
