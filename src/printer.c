/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   printer.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 17:10:06 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 15:53:33 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

//fct pour remplir title ou content, j'ai essayer de faire modulaire, je dois retravailler dessus
void			fill_str_content(int size, char *ret, char *str)
{
	int			i;

	i = 0;
	if (!*str)
		while (i < size)
			ret[i++] = '\0';
	else
	{
		while (str[i] && i < size)
		{
			ret[i] = str[i];
			i++;
		}
		while (i < size)
			ret[i++] = '\0';
	}
}

//cree le premier maillon de content
t_content		*create_content(void)
{
	t_content	*content;

	if (!(content = (t_content*)malloc(sizeof(t_content))))
		return (NULL);
	content->next = NULL;
	return (content);
}

//ajoute un maillon a content
void			add_content(t_edit *edit, char *cont, char *title, t_draw draw)
{
	t_content	*new;
	t_content	*tmp;

	if (!(new = (t_content*)malloc(sizeof(t_content))))
		return ;
	tmp = edit->con;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	fill_str_content(256, new->c_title, title);
	fill_str_content(2048, new->c_content, cont);
	new->x = draw.x;
	new->y = draw.y;
	new->display = draw.i;
	new->cursor = 0;
	new->trigger = 0;
	new->next = NULL;
}

void			tdisplay(t_edit *edit, t_draw *draw)
{
	if (edit == NULL || draw == NULL)
		return ;
}

t_draw			set_printd(int x, int y, t_draw settings)
{
	t_draw	data;

	data.x = x;
	data.y = y;
	data.y_s = settings.y_s;
	data.x_s = settings.x_s;
	return (data);
}
