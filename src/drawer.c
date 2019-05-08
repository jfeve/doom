/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   drawer.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 18:21:59 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 20:44:47 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	check_newline(t_draw *draw, t_content *temp, t_draw *cnt)
{
	if (draw->input[draw->i] == '\n')
	{
		draw->x = temp->x;
		draw->y = temp->y + (10 * draw->y_s);
		cnt->x = draw->x;
		cnt->y = draw->y;
	}
}

static void	cursor(t_draw *cnt, t_draw *draw, t_edit *edit, t_content *temp)
{
	char *tmp;

	if (temp->cursor < 4 && edit->dyn_trigger == 1)
	{
		if ((tmp = get_content_char(74)) == NULL)
			return ;
		draw->color = WHITE;
		draw_norm(cnt, draw, edit, tmp);
		draw->i += 1;
	}
}

int			draw_content(t_edit *edit, t_content *temp, t_draw *draw)
{
	t_draw		cnt;
	char		*tmp;

	draw->i = 0;
	cnt.x = draw->x;
	cnt.y = draw->y;
	while (draw->input[draw->i])
	{
		check_newline(draw, temp, &cnt);
		if ((tmp = get_content_char((int)draw->input[draw->i])) == NULL)
			return (0);
		if (ft_isdigit(draw->input[draw->i]))
			draw->color = RED;
		else
			draw->color = WHITE;
		draw_norm(&cnt, draw, edit, tmp);
		draw->i += 1;
	}
	cursor(&cnt, draw, edit, temp);
	return (1);
}
