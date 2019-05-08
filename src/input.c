/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 16:32:55 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 22:49:01 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	check_keyboard(t_input *in, t_content *tmp)
{
	int			i;
	int			j;
	int			maxkey;
	char		c;

	i = 48;
	maxkey = 98;
	while (i <= maxkey && tmp->cursor < 4)
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

static void	dyn_enter(t_edit *edit, t_input *in, t_content *tmp)
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

void		dyn_input(t_edit *edit, t_input *in)
{
	t_content	*tmp;

	tmp = edit->con;
	while (tmp->next && tmp->display == 0)
		tmp = tmp->next;
	if (edit->dyn_trigger == 0 && tmp->display == 1)
		free_dyn_content(&edit->con);
	if (edit->dyn_trigger == 1 && tmp->display == 1)
	{
		get_title(edit, tmp);
		if (in->key[SDL_SCANCODE_BACKSPACE])
		{
			if (tmp->cursor != 0)
			{
				tmp->cursor--;
				tmp->c_content[tmp->cursor] = '\0';
			}
			in->key[SDL_SCANCODE_BACKSPACE] = SDL_FALSE;
		}
		dyn_enter(edit, in, tmp);
		check_keyboard(in, tmp);
	}
}

int			check_input(t_edit *edit, t_input *in)
{
	t_content	*tmp;

	if (in->key[SDL_SCANCODE_T] && edit->hl_sec && edit->hl_sec->floor == -1)
	{
		clear_hl_vec(edit->hl_sec);
		edit->hl_vert = NULL;
		in->key[SDL_SCANCODE_T] = SDL_FALSE;
		if (add_content(edit, "", "floor = ",
			init_draw(600, HUD_BEGIN + 50, 1)) == 0)
			return (0);
		tmp = edit->con;
		while (tmp->next)
			tmp = tmp->next;
		tmp->display = 1;
		edit->dyn_trigger = 1;
	}
	return (1);
}
