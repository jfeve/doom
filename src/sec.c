/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sec.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 16:22:44 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 16:19:15 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static t_sec	*create_sec(void)
{
	t_sec		*sec;

	if (!(sec = (t_sec*)malloc(sizeof(t_sec))))
		return (NULL);
	sec->next = NULL;
	return (sec);
}

static void		add_sec(t_edit *edit)
{
	t_sec		*tmp;
	t_sec		*sec;

	if (!(sec = (t_sec*)malloc(sizeof(t_sec))))
		return ;
	sec->next = NULL;
	tmp = edit->sect;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = sec;
}

void			set_sect(t_edit *edit)
{
	t_sec		*tmp;

	edit->hud_flag = 0;
	edit->nbsect++;
	if (edit->sect == NULL)
		edit->sect = create_sec();
	else
		add_sec(edit);
	tmp = edit->sect;
	if (tmp->next)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	tmp->vert = edit->vert;
	tmp->vert->col = WHITE;
	tmp->text = 0;
	tmp->floor = 0;
	tmp->ceil = 0;
	tmp->obj = NULL;
	tmp->enem = NULL;
	edit->vert = NULL;
	edit->oldvert = NULL;
}

void			draw_sec(t_edit *edit)
{
	t_sec		*tmp;
	t_lis		*temp;

	if (edit->sect == NULL)
		return ;
	tmp = edit->sect;
	while (tmp)
	{
		temp = tmp->vert;
		if (temp->col == (int)RED)
			put_vert(edit, temp);
		while (temp->next)
		{
			bresen(mult_unit(*temp), mult_unit(*temp->next), &edit->sdl);
			temp = temp->next;
		}
		bresen(mult_unit(*temp), mult_unit(*(tmp->vert)), &edit->sdl);
		tmp = tmp->next;
	}
}
