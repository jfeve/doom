/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vec.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:57:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 15:27:21 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			draw_vec(t_edit *edit, t_input in)
{
	t_lis *tmp;
	t_lis point;

	if (edit->vert == NULL)
		return ;
	tmp = edit->vert;
	while (tmp->next != NULL)
	{
		bresen(mult_unit(*tmp), mult_unit(*tmp->next), &edit->sdl);
		tmp = tmp->next;
	}
	if (edit->oldvert != NULL)
	{
		bresen(mult_unit(*edit->oldvert), mult_unit(*tmp), &edit->sdl);
		set_sect(edit);
	}
	else
	{
		point.x = arr(in.x);
		point.y = arr(in.y);
		point.col = WHITE;
		bresen(mult_unit(*tmp), mult_unit(point), &edit->sdl);
	}
}

int				check_coord_in(t_lis *tmp, t_lis *vert, t_point *in, int flag)
{
	float		x;
	float		y;

	x = arr_float((float)in->x);
	y = arr_float((float)in->y);
	if (vert->x - tmp->x > 0 && (flag == 1 || flag == 3))
	{
		if (x < tmp->x || x > vert->x)
			return (0);
	}
	else if (flag == 1 || flag == 3)
		if (x < vert->x || x > tmp->x)
			return (0);
	if (vert->y - tmp->y > 0 && (flag == 2 || flag == 3))
	{
		if (y < tmp->y || y > vert->y)
			return (0);
	}
	else if (flag == 2 || flag == 3)
	{
		if (y < vert->y || y > tmp->y)
			return (0);
	}
	return (1);
}

int				special_check(t_lis *tmp, t_lis *vert, t_point *in, t_float f)
{
	if (tmp->y - vert->y == 0)
	{
		if (check_coord_in(tmp, vert, in, 1) == 0)
			return (0);
		if ((int)f.y == tmp->y)
			return (1);
	}
	else if (tmp->x - vert->x == 0)
	{
		if (check_coord_in(tmp, vert, in, 2) == 0)
			return (0);
		if ((int)f.x == tmp->x)
			return (1);
	}
	return (-1);
}

int				vec_here(t_lis *tmp, t_lis *vert, t_point *in)
{
	float		m;
	float		m2;
	float		mmin;
	float		mmax;
	t_float		f;

	f.x = arr_float((float)in->x);
	f.y = arr_float((float)in->y);
	if (special_check(tmp, vert, in, f) != -1)
		return (special_check(tmp, vert, in, f));
	else if (tmp->x - vert->x != 0)
	{
		if (check_coord_in(tmp, vert, in, 3) == 0)
			return (0);
		m = (((float)vert->y * UNIT) - ((float)tmp->y * UNIT)) /
			(((float)vert->x - (float)tmp->x) * UNIT);
		m2 = ((float)in->y - ((float)tmp->y * UNIT)) / ((float)in->x -
				((float)tmp->x * UNIT));
		mmin = m - 0.3f;
		mmax = m + 0.3f;
		if (m2 >= mmin && m2 <= mmax)
			return (1);
	}
	return (0);
}

int				check_on_vec(t_point *in, t_sec *sec)
{
	t_lis		*tmp;
	int			i;

	i = 1;
	if (sec == NULL)
		return (0);
	tmp = sec->vert;
	while (tmp->next)
	{
		if (vec_here(tmp, tmp->next, in) == 1)
			return (i);
		tmp = tmp->next;
		i++;
	}
	if (vec_here(tmp, sec->vert, in) == 1)
		return (i);
	return (0);
}
