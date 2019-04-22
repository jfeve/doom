/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   drawer_bis.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 18:12:32 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 16:25:04 by nzenzela    ###    #+. /#+    ###.fr     */
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
	while (j <= draw->y + draw->y_s - 1)
	{
		i = draw->x;
		while (i <= draw->x + draw->x_s - 1)
			edit->sdl.pix[j * WIN_W + i++] = draw->color;
		j++;
	}
}

t_draw			init_draw(int x, int y, int disp)
{
	t_draw		draw;

	draw.x = x;
	draw.y = y;
	draw.x_s = 0;
	draw.y_s = 0;
	draw.i = disp;
	draw.color = WHITE;
	return (draw);
}

char			*get_content_char(int num)
{
	if (check_num(num) != NULL)
		return (check_num(num));
	else if (check_alpha1(num) != NULL)
		return (check_alpha1(num));
	else if (check_alpha2(num) != NULL)
		return (check_alpha2(num));
	else if (check_alpha3(num) != NULL)
		return (check_alpha3(num));
	else if (check_spe(num) != NULL)
		return (check_spe(num));
	else
		return ("\0");
}

void			draw_checks(char c, t_draw *cnt, t_draw *draw)
{
	if (c == '\0')
	{
		cnt->x += 20;
		draw->x = cnt->x;
		draw->y = cnt->y;
	}
}

void			draw_norm(t_draw *cnt, t_draw *draw, t_edit *ed, char *tmp)
{
	int			nb;

	cnt->i = 0;
	while (tmp[cnt->i])
	{
		nb = tmp[cnt->i] - 48;
		if (tmp[cnt->i] == '1')
		{
			draw_square(ed, draw);
			draw->x += draw->x_s;
		}
		if (tmp[cnt->i] != '1' && tmp[cnt->i] != '0')
			draw->x += (draw->x_s * nb);
		if (tmp[cnt->i] != '1' && tmp[cnt->i] == '0')
			draw->x += draw->x_s;
		else if (tmp[cnt->i] == '\n')
		{
			draw->x = cnt->x;
			draw->y += draw->y_s;
		}
		draw_checks(tmp[cnt->i + 1], cnt, draw);
		cnt->i += 1;
	}
}
