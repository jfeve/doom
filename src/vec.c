/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vec.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:57:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 17:21:05 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			swap_datas(t_lis *vert, t_lis *last)
{
	t_lis tmp;

	if (!vert)
		return ;
	while (vert != last)
	{
		tmp.x = vert->x;
		tmp.y = vert->y;
		tmp.col = vert->col;
		tmp.neigh = vert->neigh;
		tmp.port = vert->port;
		vert->x = last->x;
		vert->y = last->y;
		vert->col = last->col;
		vert->port = last->port;
		vert->neigh = last->neigh;
		last->x = tmp.x;
		last->y = tmp.y;
		last->col = tmp.col;
		last->neigh = tmp.neigh;
		last->port = tmp.port;
		vert = vert->next;
	}
}

void			put_new_vert(t_edit *edit, t_input *in)
{
	t_lis		*tmp;
	t_lis		*last;

	add_vert(in->x, in->y, edit, edit->hl_sec->vert);
	last = edit->hl_sec->vert;
	while (last->next)
		last = last->next;
	last->col = RED;
	if (edit->hl_vert->next != last && edit->hl_vert->next)
		tmp = edit->hl_vert->next;
	else
		tmp = edit->hl_sec->vert;
	swap_datas(tmp, last);
	tmp->col = RED;
	if (tmp->next)
		tmp->next->col = GREEN;
	else
		edit->hl_sec->vert->col = GREEN;
	edit->hl_vert = tmp;
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

int				vec_here(t_lis *tmp, t_lis *vert, t_point *in)
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
		return(i);
	return (0);
}
