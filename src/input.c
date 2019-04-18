/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 16:32:55 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 20:00:48 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"


// void						draw_text(t_edit *edit)
// {
// 	int						x;
// 	int						y;
// 	int						i;
// 	int						nb;

// 	tmp = vert;
// 	while (tmp && tmp->text != -1)
// 		tmp = tmp->next;
// 	if (tmp == NULL)
// 		return (0);
// 	return (1);
// }

/*
 *void						edit_input(t_edit *edit)
 *{
 *    int		x;
 *    int		y;
 *    int		i;
 *    int		nb;
 *
 *    i = 0;
 *    nb = 0;
 *    x = 600;
 *    y = HUD_BEGIN;
 *    if (edit->input_flag == 1)
 *    {
 *        while (edit->input_list[i] && edit->input_list[i] != ' ')
 *        {
 *            nb = edit->input_list[i] - 48;
 *            draw_num(edit, write_num(x += 20, 900, 1), nb);
 *            i++;
 *        }
 *        draw_num(edit, write_num(x += 15, 900, 4), 10);
 *    }
 *}
 *
 *void			edit_mode(t_input *in, t_edit *edit)
 *{
 *    int		minkey;
 *    int		maxkey;
 *    int		i;
 *    int		j;
 *    int		k;
 *
 *    k = 0;
 *    minkey = 89;
 *    maxkey = 98;
 *    i = minkey;
 *    j = 0;
 *    if (in->key[SDL_SCANCODE_KP_ENTER] && edit->input_trigger == 1)
 *    {
 *        edit->input_cursor = 0;
 *        edit->input_res = ft_atoi(edit->input_list);
 *        handle_res(edit);
 *        while (k < 9)
 *        {
 *            edit->input_list[k] = 0;
 *            k++;
 *        }
 *        k = 0;
 *        in->key[SDL_SCANCODE_KP_ENTER] = SDL_FALSE;
 *    }
 *    if (in->key[SDL_SCANCODE_BACKSPACE])
 *    {
 *        edit->input_trigger = 0;
 *        if (edit->input_cursor != 0)
 *        {
 *            if (edit->input_list[edit->input_cursor - 1] != ' ')
 *            {
 *                edit->input_list[edit->input_cursor - 1] = ' ';
 *                edit->input_cursor--;
 *            }
 *        }
 *        edit->input_trigger = 1;
 *        in->key[SDL_SCANCODE_BACKSPACE] = SDL_FALSE;
 *    }
 *    while (i <= maxkey && edit->input_trigger == 1)
 *    {
 *        if (in->key[i])
 *        {
 *            if (i != 98)
 *                j = i - 88;
 *            else if (i == 98)
 *                j = 0;
 *            edit->input_flag = 1;
 *            if (edit->input_cursor != 9)
 *            {
 *                edit->input_list[edit->input_cursor] = (j + '0');
 *                edit->input_cursor++;
 *            }
 *            in->key[i] = SDL_FALSE;
 *            j = 0;
 *        }
 *        i++;
 *    }
 *}
 *
 *void			init_text(t_text *text)
 *{
 *    text->c_cursor = 0;
 *    text->c_flag = 0;
 *    text->c_trigger = 0;
 *    text->content = NULL;
 *}
 */

void			free_dyn_content(t_content **con)
{
	t_content	*tmp;

	tmp = *con;
	while (tmp->next)
	{
		if (tmp->next->next == NULL)
			break ;
	}
	free(tmp->next);
	tmp->next = NULL;
}

void			dyn_input(t_edit *edit, t_input *in)
{
	t_content	*tmp;
	int		i;
	int		j;
	int		maxkey;
	char	c;

	i = 89;
	maxkey = 98;
	tmp = edit->con;
	while (tmp->next && tmp->display == 0)
		tmp = tmp->next;
	if (edit->dyn_trigger == 0 && tmp->display == 1)
	{
		free_dyn_content(&edit->con);
	}
	if (edit->dyn_trigger == 1 && tmp->display == 1)
	{
		if (in->key[SDL_SCANCODE_BACKSPACE])
		{
			if (tmp->cursor != 0)
			{
				tmp->cursor--;
				tmp->c_content[tmp->cursor] = '\0';
			}
			in->key[SDL_SCANCODE_BACKSPACE] = SDL_FALSE;
		}
		if (in->key[SDL_SCANCODE_KP_ENTER])
		{
			edit->input_res = ft_atoi(tmp->c_content);
			handle_res(edit);
			while (tmp->cursor > 0)
			tmp->c_content[--tmp->cursor] = '\0';
			in->key[SDL_SCANCODE_KP_ENTER] = SDL_FALSE;
		}
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
}

//cree un maillon content avec trigger = 1 si T appuyer 
void			check_input(t_edit *edit, t_input *in)
{
	t_content	*tmp;

	if (in->key[SDL_SCANCODE_T] && edit->hl_sec)
	{
		in->key[SDL_SCANCODE_T] = SDL_FALSE;
		add_content(edit, "", "floor = ", init_draw(600, HUD_BEGIN + 50, 1));
		tmp = edit->con;
		while (tmp->next)
			tmp = tmp->next;
		tmp->display = 1;
		edit->dyn_trigger = 1;
	}
}
