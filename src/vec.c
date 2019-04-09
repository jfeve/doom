/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vec.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:57:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 00:56:31 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				check_coord_in(t_lis *tmp, t_lis *vert, t_input *in, int flag)
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
	{
		if (x < vert->x || x > tmp->x)
			return (0);
	}
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

int				vec_here(t_lis *tmp, t_lis *vert, t_input *in)
{
	float		m;
	float		mmin;
	float		mmax;
	float		m2;
	float		x;
	float		y;

	x = arr_float((float)in->x);
	y = arr_float((float)in->y);
	if (tmp->y - vert->y == 0)
	{
		if (check_coord_in(tmp, vert, in, 1) == 0)
			return (0);
		if ((int)y == tmp->y)
			return (1);
	}
	else if (tmp->x - vert->x == 0)
	{
		if (check_coord_in(tmp, vert, in, 2) == 0)
			return (0);
		if ((int)x == tmp->x)
			return (1);
	}
	else if (tmp->x - vert->x != 0)
	{
		if (check_coord_in(tmp, vert, in, 3) == 0)
			return (0);
		m = (((float)vert->y * UNIT) - ((float)tmp->y * UNIT)) / (((float)vert->x - (float)tmp->x) * UNIT);
		m2 = ((float)in->y - ((float)tmp->y * UNIT)) / ((float)in->x - ((float)tmp->x * UNIT));
		mmin = m - 0.3f;
		mmax = m + 0.3f;
		printf("m = %f, m2 = %f\n", m, m2);
		if (m2 >= mmin && m2 <= mmax)
			return (1);
	}
	return (0);
}

int				check_on_vec(t_edit *edit, t_input *in)
{
	t_lis		*tmp;
	t_sec		*sec;

	if (edit->sect == NULL)
		return (0);
	sec = edit->sect;
	while (sec)
	{
		tmp = sec->vert;
		while (tmp->next)
		{
			if (vec_here(tmp, tmp->next, in) == 1)
				return (1);
			tmp = tmp->next;
		}
		if (vec_here(tmp, sec->vert, in) == 1)
			return(1);
		sec = sec->next;
	}
	return (0);
}
