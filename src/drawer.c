/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   drawer.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 18:21:59 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 16:27:23 by nzenzela    ###    #+. /#+    ###.fr     */
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
	else
		return (NULL);
}

void			draw_content(t_edit *edit, t_draw *draw)
{
	int		x;
	int		y;
	int		nb;
	int		j;
	char	*tmp;

	draw->i = 0;
	x = draw->x;
	y = draw->y;
	while (draw->input[draw->i] != '\0')
	{
		j = 0;
		dprintf(1, "\n\n%s\n\n", get_content_char(draw->input[draw->i]));
		return ;
		tmp = (char*)malloc(sizeof(char) * 500);
		if ((tmp = get_content_char((int)draw->input[draw->i])) == NULL)
			return ;
		while (tmp[j] != '\0')
		{
			nb = tmp[j] - 48;
			if (tmp[j] == '1')
			{
				draw->x += draw->x_s;
				draw_square(edit, draw);
			}
			if (tmp[j] != '1' && tmp[j] != '0')
				draw->x += (draw->x_s * nb);
			if (tmp[j] != '1' && tmp[j] == '0')
				draw->x += draw->x_s;
			else if (tmp[j] == '\n')
			{
				draw->x = x;
				draw->y += draw->y_s;
			}
		}
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
		len = (ft_strlen(tmp->c_title) + ft_strlen(tmp->c_content) + 2);
		if ((draw->input = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
			return ;
		draw->input[0] = '\0';
		ft_strcat(draw->input, tmp->c_title);
		ft_strcat(draw->input, tmp->c_content);
		draw->input[len] = '.';
		len = 0;
		if (draw->input != NULL)
			free(draw->input);
		tmp = tmp->next;
	}
}

void		prepare_draw(t_edit *edit)
{
	t_draw		draw;

	get_string(edit, &draw);
	dprintf(1, "\n\n\n%s\n\n\n", draw.input);
	draw.y_s = 4;
	draw.x_s = 2;
	draw.color = WHITE;
	draw_content(edit, &draw);
}
