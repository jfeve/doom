/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/21 22:03:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:08:20 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			add_equal(t_content **temp, int j)
{
	t_content	*cont;

	cont = *temp;
	cont->c_title[j++] = ' ';
	cont->c_title[j++] = '=';
	cont->c_title[j++] = ' ';
}

void			get_lis_num(t_content **con, t_lis *vert)
{
	t_content	*temp;
	t_lis		*tmp;
	int			i;
	int			j;
	char		*str;

	tmp = vert;
	i = 1;
	j = 0;
	temp = *con;
	while (tmp && tmp->text != -1)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	str = ft_itoa(i);
	i = 0;
	while (temp->c_title[j])
		j++;
	while (str[i])
		temp->c_title[j++] = str[i++];
	add_equal(&temp, j);
}

void			get_title(t_edit *edit, t_content **con)
{
	t_sec		*hl;
	t_content	*tmp;

	hl = edit->hl_sec;
	tmp = *con;
	if (hl->floor == -1)
		fill_str_content(256, tmp->c_title, FLOOR);
	else if (hl->ceil == -1)
		fill_str_content(256, tmp->c_title, CEIL);
	else if (check_lis_input(hl->vert))
	{
		fill_str_content(256, tmp->c_title, VEC);
		get_lis_num(&tmp, hl->vert);
	}
	else if (check_lis_input(hl->obj))
	{
		fill_str_content(256, tmp->c_title, OBJ);
		get_lis_num(&tmp, hl->obj);
	}
	else if (check_lis_input(hl->enem))
	{
		fill_str_content(256, tmp->c_title, ENEM);
		get_lis_num(&tmp, hl->enem);
	}
}

void			check_keyboard(t_input *in, t_content *tmp)
{
	int			i;
	int			j;
	int			maxkey;
	char		c;

	i = 48;
	maxkey = 98;
	while (i <= maxkey)
	{
		if (in->key[i])
		{
			if (i != 98)
				j = i - 88;
			else
				j = 0;
			c = j + '0';
			j = 0;
			tmp->c_content[tmp->cursor] = c;
			tmp->cursor++;
			in->key[i] = SDL_FALSE;
		}
		i++;
	}
}

void			dyn_enter(t_edit *edit, t_input *in, t_content *tmp)
{
	if (in->key[SDL_SCANCODE_KP_ENTER] || in->key[SDL_SCANCODE_RETURN])
	{
		edit->input_res = ft_atoi(tmp->c_content);
		if (edit->input_res != 0)
			handle_res(edit);
		while (tmp->cursor > 0)
			tmp->c_content[--tmp->cursor] = '\0';
		tmp->c_content[0] = '\0';
		in->key[(in->key[SDL_SCANCODE_RETURN] ? SDL_SCANCODE_RETURN
				: SDL_SCANCODE_KP_ENTER)] = SDL_FALSE;
	}
}
