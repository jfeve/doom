/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prepare_draw.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 20:19:25 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 20:11:15 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	norm_string(t_content *tmp, t_draw *draw)
{
	ft_strcat(draw->input, tmp->c_title);
	ft_strcat(draw->input, tmp->c_content);
	draw->x = tmp->x;
	draw->y = tmp->y;
}

static int	get_string(t_edit *edit, t_draw *draw)
{
	t_content	*tmp;
	int			len;

	tmp = edit->con;
	draw->input = NULL;
	if (ft_strlen(tmp->c_title) == 0 && ft_strlen(tmp->c_content) == 0)
		return (0);
	while (tmp != NULL)
	{
		if (tmp->trigger == 1)
		{
			len = (ft_strlen(tmp->c_title) + ft_strlen(tmp->c_content) + 2);
			if ((draw->input = (char *)
					malloc(sizeof(char) * (len + 1))) == NULL)
				return (0);
			draw->input[0] = '\0';
			norm_string(tmp, draw);
			len = 0;
			draw_content(edit, tmp, draw);
			free(draw->input);
		}
		tmp = tmp->next;
	}
	return (1);
}

int			prepare_draw(t_edit *edit)
{
	t_draw		draw;

	draw.y_s = 3;
	draw.x_s = 2;
	draw.color = WHITE;
	if (get_string(edit, &draw) == 0)
		return (0);
	return (1);
}
