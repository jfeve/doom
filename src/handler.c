/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handler.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 17:31:23 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 17:31:38 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void						handle_res(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->vert;
	if (edit->hl_sec->floor == -1)
		edit->hl_sec->floor = edit->input_res;
	else if (edit->hl_sec->ceil == -1)
	{
		edit->hl_sec->ceil = edit->input_res;
		edit->hl_vert = edit->hl_sec->vert;
		edit->hl_vert->next->col = GREEN;
	}
	else if (check_lis_input(tmp))
	{
		while (tmp->next && tmp->text != -1)
			tmp = tmp->next;
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
		{
			if (edit->hl_sec->obj)
			{
				edit->hl_sec->obj->oldcol = edit->hl_sec->obj->col;
				edit->hl_sec->obj->col = BROWN;
			}
			edit->hl_sec->vert->col = edit->hl_sec->vert->oldcol;
			edit->hl_vert = NULL;
		}
	}
	else if (check_lis_input(edit->hl_sec->obj))
	{
		tmp = edit->hl_sec->obj;
		while (tmp->next && tmp->text != -1)
			tmp = tmp->next;
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
			tmp->col = tmp->oldcol;
		}
	}
	else if (check_lis_input(edit->hl_sec->enem))
	{
		tmp = edit->hl_sec->enem;
		while (tmp->next && tmp->text != -1)
			tmp = tmp->next;
		tmp->text = edit->input_res;
		if (tmp->next)
		{
			tmp->next->oldcol = tmp->next->col;
			tmp->next->col = tmp->col;
			tmp->col = tmp->oldcol;
		}
		else
		{
			tmp->col = tmp->oldcol;
			edit->input_flag = 0;
			edit->input_trigger = 0;
		}
	}
}