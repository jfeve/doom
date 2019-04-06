/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vert.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:21:04 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 16:36:11 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				arr(int x)
{
	if (x % UNIT >= UNIT / 2)
		x += UNIT / 2 + 1;
	return (x / UNIT);
}

t_lis			*create_vert(int x, int y)
{
	t_lis		*vert;

	if (!(vert = (t_lis*)malloc(sizeof(t_lis))))
		return (NULL);
	vert->x = arr(x);
	vert->y = arr(y);
	vert->col = RED;
	vert->next = NULL;
	return (vert);
}

int				parse_data(int x, int y, t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->vert;
	if (tmp->x == arr(x) && tmp->y == arr(y))
	{
		edit->oldvert = tmp;
		return (0);
	}
	edit->oldvert = NULL;
	return (1);
}

void			add_vert(int x, int y, t_edit *edit)
{
	t_lis		*point;
	t_lis		*tmp;

	if (parse_data(x, y, edit) == 0)
		return ;
	if (!(point = (t_lis*)malloc(sizeof(t_lis))))
		return ;
	point->x = arr(x);
	point->y = arr(y);
	point->col = WHITE;
	point->next = NULL;
	tmp = edit->vert;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = point;
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

void			put_vert(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->vert;
	while (tmp != NULL)
	{
		draw_vert(tmp, edit);
		tmp = tmp->next;
	}
}
