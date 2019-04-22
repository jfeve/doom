/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   drawer.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 18:21:59 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 18:56:31 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			check_newline(t_draw *draw, t_content *temp, t_draw *cnt)
{
	if (draw->input[draw->i] == '\n')
	{
		draw->x = temp->x;
		draw->y = temp->y + (10 * draw->y_s);
		cnt->x = draw->x;
		cnt->y = draw->y;
	}
}

void			draw_content(t_edit *edit, t_content *temp, t_draw *draw)
{
	t_draw		cnt;
	char		*tmp;

	draw->i = 0;
	cnt.x = draw->x;
	cnt.y = draw->y;
	while (draw->input[draw->i])
	{
		check_newline(draw, temp, &cnt);
		if (!(tmp = (char*)malloc(sizeof(char) *
			ft_strlen(get_content_char(draw->input[draw->i])))))
			return ;
		if ((tmp = get_content_char((int)draw->input[draw->i])) == NULL)
			return ;
		if (ft_isdigit(draw->input[draw->i]))
			draw->color = RED;
		else
			draw->color = WHITE;
		draw_norm(&cnt, draw, edit, tmp);
		draw->i += 1;
	}
}

void			norm_string(t_content *tmp, t_draw *draw)
{
	ft_strcat(draw->input, tmp->c_title);
	ft_strcat(draw->input, tmp->c_content);
	draw->x = tmp->x;
	draw->y = tmp->y;
}

void			get_string(t_edit *edit, t_draw *draw)
{
	t_content	*tmp;
	int			len;

	tmp = edit->con;
	draw->input = NULL;
	if (ft_strlen(tmp->c_title) == 0 && ft_strlen(tmp->c_content) == 0)
		return ;
	while (tmp != NULL)
	{
		if (tmp->trigger == 1)
		{
			len = (ft_strlen(tmp->c_title) + ft_strlen(tmp->c_content) + 2);
			if ((draw->input = (char *)
					malloc(sizeof(char) * (len + 1))) == NULL)
				return ;
			draw->input[0] = '\0';
			norm_string(tmp, draw);
			len = 0;
			draw_content(edit, tmp, draw);
			if (draw->input != NULL)
				free(draw->input);
		}
		tmp = tmp->next;
	}
}

void			prepare_draw(t_edit *edit)
{
	t_draw		draw;

	draw.y_s = 3;
	draw.x_s = 2;
	draw.color = WHITE;
	get_string(edit, &draw);
}
