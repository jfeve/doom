/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   printer.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 17:10:06 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 20:24:08 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			tadd_title(t_text *content)
{
	if (content == NULL)
		return ;
	return ;
}

t_content		create_content(void)
{
	t_content	*content;
	return (content);
}

void			tdisplay(t_edit *edit, t_text *content, t_draw *draw)
{
	if (edit == NULL || content == NULL || draw == NULL)
		return ;
}

t_draw			set_printd(int x, int y, t_draw settings)
{
	t_draw	data;

	data.x = x;
	data.y = y;
	data.y_s = settings.y_s;
	data.x_s = settings.x_s;
	data.color = settings.col;
	return (data);
}
