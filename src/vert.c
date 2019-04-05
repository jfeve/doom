/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vert.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:21:04 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 19:16:40 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

t_lis			*create_vert(int x, int y)
{
	t_lis		*vert;

	if (!(vert = (t_lis*)malloc(sizeof(t_lis))))
		return (NULL);
	vert->x = x - (x % 10);
	vert->y = y - (y % 10);
	vert->next = NULL;
	return (vert);
}

int				parse_data(int x, int y, t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->vert;
	while(tmp != NULL)
	{
		if (tmp->x == x - (x % 10) && tmp->y == y - (y % 10))
		{
			edit->oldvert = tmp;
			return (0);
		}
		tmp = tmp->next;
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
	point->x = x - (x % 10);
	point->y = y - (y % 10);
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

	x = tmp->x - 4;
	y = tmp->y - 4;
	while (x <= tmp->x + 4)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[(y + 8) * WIN_W + x] = WHITE;
		x++;
	}
	while (y <= tmp->y + 4)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[y * WIN_W + (x - 9)] = WHITE;
		y++;
	}
	edit->sdl.pix[tmp->y * WIN_W + tmp->x] = WHITE;
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
