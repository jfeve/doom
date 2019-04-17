/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   drawer.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 18:21:59 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 19:43:06 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			draw_square(t_edit *edit, t_draw *draw)
{
	int i;
	int j;

	i = draw->x;
	j = draw->y;
	while (j <= draw->y + draw->y_s)
	{
		i = draw->x;
		while (i <= draw->x + draw->x_s)
			edit->sdl.pix[j * WIN_W + i++] = draw->color;
		j++;
	}
}

void			draw_content(t_edit *content, t_draw *draw)
{
	int		x;
	int		nb;

	draw->i = 0;
	x = draw->x;
	y = draw->y;
	while (draw->input[draw->i])
	{
		nb = draw->input[draw->i] - 48;
		if (draw->input[draw->i] == '1')
		{
			draw->x += draw->x_s;
			draw_square(edit, draw);
		}
		if (draw->input[draw->i] != '1' && draw->input[draw->i] != '0')
			draw->x += (draw->x_s * nb);
		if (draw->input[draw->i] != '1' && draw->input[draw->i] == '0')
			draw->x += draw->x_s;
		else if (draw->input[draw->i] == '\n')
		{
			draw->x = x;
			draw->y += draw->y_s;
		}
		draw->i += 1;
	}
}

void		draw_num(t_edit *edit, t_draw data, int num)
{
	t_draw					draw;

	draw.input = check_num(num);
	draw.x = data.x;
	draw.y = data.y;
	draw.y_s = data.y_s;
	draw.x_s = data.y_s;
	draw.color = check_color(data.color);
	draw_content(edit, &draw);
}
