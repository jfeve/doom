/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_res.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 13:56:35 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 21:07:14 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int			check_lis_input(t_lis *vert)
{
	t_lis		*tmp;

	tmp = vert;
	while (tmp && tmp->text != -1)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	return (1);
}

static void	handle_after_vec(t_edit *edit)
{
	if (edit->hl_sec->obj)
	{
		edit->hl_sec->obj->oldcol = edit->hl_sec->obj->col;
		edit->hl_sec->obj->col = BROWN;
	}
	else if (edit->hl_sec->enem)
	{
		edit->hl_sec->enem->oldcol = edit->hl_sec->enem->col;
		edit->hl_sec->enem->col = BROWN;
	}
	else
		edit->dyn_trigger = 0;
	edit->hl_sec->vert->col = edit->hl_sec->vert->oldcol;
	edit->hl_vert = NULL;
}

static void	handle_vec(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->vert;
	while (tmp->next && tmp->text != -1)
		tmp = tmp->next;
	if (edit->input_res > 4)
		return ;
	tmp->text = edit->input_res;
	if (tmp->next)
	{
		edit->hl_vert = tmp->next;
		edit->hl_vert->col = edit->hl_vert->oldcol;
		if (edit->hl_vert->next)
		{
			edit->hl_vert->next->oldcol = edit->hl_vert->next->col;
			edit->hl_vert->next->col = GREEN;
		}
		else
		{
			edit->hl_sec->vert->oldcol = edit->hl_sec->vert->col;
			edit->hl_sec->vert->col = GREEN;
		}
	}
	else
		handle_after_vec(edit);
}

static void	handle_obj(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->obj;
	while (tmp->next && tmp->text != -1)
		tmp = tmp->next;
	if (edit->input_res > 4)
		return ;
	tmp->text = edit->input_res;
	if (tmp->next)
	{
		tmp->next->oldcol = tmp->next->col;
		tmp->next->col = tmp->col;
		tmp->col = tmp->oldcol;
	}
	else
	{
		if (edit->hl_sec->enem)
		{
			edit->hl_sec->enem->oldcol = edit->hl_sec->enem->col;
			edit->hl_sec->enem->col = BROWN;
		}
		else
			edit->dyn_trigger = 0;
		tmp->col = tmp->oldcol;
	}
}

void		handle_res(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->vert;
	if (edit->hl_sec->gravity == -1)
	{
		if (edit->hl_sec->gravity > 5)
			return ;
		else
			edit->hl_sec->gravity = edit->input_res;
	}
	else if (edit->hl_sec->floor == -1)
		edit->hl_sec->floor = edit->input_res;
	else if (edit->hl_sec->ceil == -1 && edit->input_res > edit->hl_sec->floor)
	{
		edit->hl_sec->ceil = edit->input_res;
		edit->hl_vert = edit->hl_sec->vert;
		edit->hl_vert->next->col = GREEN;
	}
	else if (check_lis_input(tmp))
		handle_vec(edit);
	else if (check_lis_input(edit->hl_sec->obj))
		handle_obj(edit);
	else if (check_lis_input(edit->hl_sec->enem))
		handle_enem(edit);
}
