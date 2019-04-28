/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   objenem.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/14 16:13:31 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 19:32:08 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			handle_obj(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->obj;
	while (tmp->next && tmp->text != -1)
		tmp = tmp->next;
	if (edit->input_res > 2)
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
			put_zer_flag(edit);
		tmp->col = tmp->oldcol;
	}
}

void			handle_enem(t_edit *edit)
{
	t_lis		*tmp;

	tmp = edit->hl_sec->enem;
	while (tmp->next && tmp->text != -1)
		tmp = tmp->next;
	if (edit->input_res > 2)
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
		put_zer_flag(edit);
		tmp->col = tmp->oldcol;
	}
}

void			draw_obj_enem(t_edit *edit)
{
	t_sec		*temp;

	if (edit->sect == NULL)
		return ;
	temp = edit->sect;
	while (temp)
	{
		if (temp->obj)
			put_vert(edit, temp->obj);
		if (temp->enem)
			put_vert(edit, temp->enem);
		temp = temp->next;
	}
}

static	int		count_lis(t_lis *lst)
{
	t_lis	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	if (lst == NULL)
		return (0);
	while (tmp != NULL)
	{
		count += 1;
		tmp = tmp->next;
	}
	return (count);
}

static	void	check_objs(t_edit *edit)
{
	if (edit->hl_sec->obj != NULL && (edit->hl_sec->objscount + 1) > 10)
	{
		free_lis(&edit->hl_sec->obj);
		edit->hl_sec->objscount = 0;
	}
}

int				obj(t_edit *edit, t_input *in)
{
	t_lis *tmp;

	if (in->key[SDL_SCANCODE_O] && edit->hl_sec)
	{
		in->key[SDL_SCANCODE_O] = SDL_FALSE;
		check_objs(edit);
		if (edit->hl_sec->obj == NULL)
		{
			edit->hl_sec->obj = create_vert(in->x, in->y);
			if (edit->hl_sec->obj == NULL)
				return (0);
		}
		else if (edit->hl_sec->obj->text == -1)
		{
			if (add_vert(in->x, in->y, edit, edit->hl_sec->obj) == -1)
				return (0);
		}
		edit->hl_sec->objscount = count_lis(edit->hl_sec->obj);
		tmp = edit->hl_sec->obj;
		while (tmp->next)
			tmp = tmp->next;
		tmp->col = GREEN;
	}
	return (1);
}

static	void	check_enem(t_edit *edit)
{
	if (edit->hl_sec->enem != NULL && (edit->hl_sec->enemcount + 1) > 10)
	{
		free_lis(&edit->hl_sec->enem);
		edit->hl_sec->enemcount = 0;
	}
}

int				enem(t_edit *edit, t_input *in)
{
	t_lis		*tmp;

	if (in->key[SDL_SCANCODE_E] && edit->hl_sec)
	{
		in->key[SDL_SCANCODE_E] = SDL_FALSE;
		check_enem(edit);
		if (edit->hl_sec->enem == NULL)
		{
			edit->hl_sec->enem = create_vert(in->x, in->y);
			if (edit->hl_sec->enem == NULL)
				return (0);
		}
		else if (edit->hl_sec->enem->text == -1)
		{
			if (add_vert(in->x, in->y, edit, edit->hl_sec->enem) == -1)
				return (0);
		}
		edit->hl_sec->enemcount = count_lis(edit->hl_sec->enem);
		tmp = edit->hl_sec->enem;
		while (tmp->next)
			tmp = tmp->next;
		tmp->col = RED;
	}
	return (1);
}
