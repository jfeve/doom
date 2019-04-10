/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 16:32:55 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 20:44:35 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"


unsigned int				check_color(char c)
{
	if (c == '1')
		return (RED);
	else if (c == '2')
		return (CYAN);
	else if (c == '3')
		return (GREEN);
	else
		return (WHITE);	
}

char						*check_num(int num)
{
	if (num == 1)
		return (_1_);
	else if (num == 2)
		return (_2_);
	else if (num == 3)
		return (_3_);
	else if (num == 4)
		return (_4_);
	else if (num == 5)
		return (_5_);
	else if (num == 6)
		return (_6_);
	else if (num == 7)
		return (_7_);
	else if (num == 8)
		return (_8_);
	else if (num == 9)
		return (_9_);
	else
		return (0);	
}

void						draw_square(t_edit *edit, t_draw *draw)
{
	int i = draw->x;
	int j = draw->y;

	while (j <= draw->y + draw->y_s)
	{
		i = draw->x;
		while (i <= draw->x + draw->x_s)
		{
			edit->sdl.pix[j * WIN_W + i] = RED;
			i++;
		} 
		j++;
	}
}

void						draw_num(t_edit *edit,int x, int y, int num)
{
	t_draw	draw;

	draw.input = check_num(num);
	draw.y_s = 8;
	draw.x_s = 6;
	draw.i = 0;
	draw.x = x;
	draw.y = y;

	while (draw.input[draw.i])
	{
		if (draw.input[draw.i] != '0' && (draw.input[draw.i] > '0' && draw.input[draw.i] <= '3'))
		{
			draw.color = check_color(draw.input[draw.i]);
			draw.x += draw.x_s;
			draw_square(edit, &draw);
		}
		if (draw.input[draw.i] == '0')
			draw.x += draw.x_s;
		else if (draw.input[draw.i] == '\n')
		{
			draw.x = x;
			draw.y += draw.y_s;
		}
		draw.i++;
	}
}
