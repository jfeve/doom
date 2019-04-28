/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vert.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:21:04 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 11:11:51 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

t_lis			*create_vert(int x, int y)
{
	t_lis		*vert;

	if (!(vert = (t_lis*)malloc(sizeof(t_lis))))
		return (NULL);
	vert->x = arr(x);
	vert->y = arr(y);
	vert->neigh = -1;
	vert->text = -1;
	vert->port = 0;
	vert->col = RED;
	vert->oldcol = RED;
	vert->next = NULL;
	return (vert);
}

int				parse_data(int x, int y, t_edit *edit, t_lis *vert)
{
	t_lis		*tmp;

	tmp = vert;
	if (tmp->x == arr(x) && tmp->y == arr(y))
	{
		if (tmp->next)
			edit->oldvert = tmp;
		return (0);
	}
	edit->oldvert = NULL;
	return (1);
}

int				add_vert(int x, int y, t_edit *edit, t_lis *vert)
{
	t_lis		*point;
	t_lis		*tmp;

	if (parse_data(x, y, edit, vert) == 0)
		return (0);
	if (!(point = (t_lis*)malloc(sizeof(t_lis))))
		return (-1);
	point->x = arr(x);
	point->neigh = -1;
	point->port = 0;
	point->text = -1;
	point->y = arr(y);
	point->col = WHITE;
	point->oldcol = RED;
	point->next = NULL;
	tmp = vert;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		if (tmp->x == point->x && tmp->y == point->y)
		{
			free(point);
			return (0);
		}
	}
	tmp->next = point;
	return (1);
}

void			draw_vert(t_lis *tmp, t_edit *edit)
{
	int x;
	int y;

	x = (tmp->x * UNIT) - 4;
	y = (tmp->y * UNIT) - 4;
	while (x <= (tmp->x * UNIT) + 4)
	{
		edit->sdl.pix[y * WIN_W + x] = tmp->col;
		edit->sdl.pix[(y + 8) * WIN_W + x] = tmp->col;
		x++;
	}
	while (y <= (tmp->y * UNIT) + 4)
	{
		edit->sdl.pix[y * WIN_W + x] = tmp->col;
		edit->sdl.pix[y * WIN_W + (x - 9)] = tmp->col;
		y++;
	}
	edit->sdl.pix[tmp->y * UNIT * WIN_W + (tmp->x * UNIT)] = tmp->col;
}

void			put_vert(t_edit *edit, t_lis *vert)
{
	t_lis		*tmp;
	int			co;

	tmp = vert;
	while (tmp != NULL)
	{
		if (tmp == edit->hl_vert)
		{
			co = tmp->col;
			tmp->col = GREEN;
			draw_vert(tmp, edit);
			tmp->col = co;
		}
		else if (tmp->port == 1)
		{
			co = tmp->col;
			tmp->col = PURPLE;
			draw_vert(tmp, edit);
			tmp->col = co;
		}
		else
			draw_vert(tmp, edit);
		tmp = tmp->next;
	}
}
