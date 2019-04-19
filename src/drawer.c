/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   drawer.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 18:21:59 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 21:35:17 by jfeve       ###    #+. /#+    ###.fr     */
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

t_draw			init_draw(int x, int y, int disp)
{
	t_draw		draw;

	draw.x = x;
	draw.y = y;
	draw.x_s = 2;
	draw.y_s = 3;
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
	else if (num == '\t' || num == ' ')
		return ("\t\0");
	else
		return (ft_strdup("\0"));
}

void			draw_norm(t_draw *cnt, t_draw *draw, t_edit *ed, char *tmp)
{
	int			nb;

	cnt->i = 0;
	while (tmp[cnt->i] != '\0')
	{
		nb = tmp[cnt->i] - 48;
		if (tmp[cnt->i] == '1')
		{
			draw->x += draw->x_s;
			draw_square(ed, draw);
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
		if (tmp[cnt->i + 1] == '\0')
		{
			cnt->x += 45;
			draw->x = cnt->x;
			draw->y = cnt->y;
		}
		cnt->i += 1;
	}
}

void			draw_content(t_edit *edit, t_draw *draw)
{
	t_draw		cnt;
	char		*tmp;

	draw->i = 0;
	cnt.x = draw->x;
	cnt.y = draw->y;
	while (draw->input[draw->i] != '\0')
	{
		tmp = (char*)malloc(sizeof(char) *
			ft_strlen(get_content_char(draw->input[draw->i])));
		if ((tmp = get_content_char((int)draw->input[draw->i])) == NULL)
			return ;
		draw_norm(&cnt, draw, edit, tmp);
		draw->i += 1;
	}
}

void		get_string(t_edit *edit, t_draw *draw)
{
	t_content	*tmp;
	int			len;

	len = 0;
	tmp = edit->con;
	draw->input = NULL;
	if (ft_strlen(tmp->c_title) == 0 && ft_strlen(tmp->c_content) == 0)
		return ;
	while (tmp != NULL)
	{
		if (tmp->trigger == 1)
		{
			len = (ft_strlen(tmp->c_title) + ft_strlen(tmp->c_content) + 2);
			if ((draw->input = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
				return ;
			draw->input[0] = '\0';
			ft_strcat(draw->input, tmp->c_title);
			ft_strcat(draw->input, tmp->c_content);
			draw->input[len] = '.';
			draw->x = tmp->x;
			draw->y = tmp->y;
			len = 0;
			draw_content(edit, draw);
			if (draw->input != NULL)
				free(draw->input);
		}
		tmp = tmp->next;
	}
}

void		prepare_draw(t_edit *edit)
{
	t_draw		draw;

	draw.y_s = 6;
	draw.x_s = 5;
	draw.color = WHITE;
	get_string(edit, &draw);
}
