/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 16:32:55 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 15:31:38 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

t_draw							write_num(int x, int y, int col)
{
	t_draw						data;

	data.x = x;
	data.y = y;
	data.y_s = 2;
	data.x_s = 1;
	data.color = col;
	return (data);
}

int								check_color(int c)
{
	if (c == 1)
		return (RED);
	else if (c == 2)
		return (CYAN);
	else if (c == 3)
		return (GREEN);
	else if (c == 4)
		return (DARK);
	else
		return (WHITE);
}

char							*check_num(int num)
{
	if (num == 1)
		return (_1_);
	else if (num == 2)
		return (_2_);
	else if (num == 3)
		return (_3_);
	else if (num == 4)
		return (_4_);
	else if (num == 5)
		return (_5_);
	else if (num == 6)
		return (_6_);
	else if (num == 7)
		return (_7_);
	else if (num == 8)
		return (_8_);
	else if (num == 9)
		return (_9_);
	else if (num == 0)
		return (_0_);
	else if (num == 10)
		return (_I_);
	else if (num == 11)
		return (_E_);
	else if (num == 12)
		return (_S_);
	else
		return (0);
}

void							draw_square(t_edit *edit, t_draw *draw)
{
	int							i;
	int							j;

	i = draw->x;
	j = draw->y;
	while (j <= draw->y + draw->y_s)
	{
		i = draw->x;
		while (i <= draw->x + draw->x_s)
		{
			edit->sdl.pix[j * WIN_W + i] = draw->color;
			i++;
		}
		j++;
	}
}

void						draw_(t_edit *edit, t_draw *draw)
{
	int						x;
	int						nb;

	draw->i = 0;
	x = draw->x;
	nb = 0;
	while (draw->input[draw->i])
	{
		nb = draw->input[draw->i] - 48;
		if (draw->input[draw->i] == '1')
		{
			draw->x += draw->x_s;
			draw_square(edit, draw);
		}
		if (draw->input[draw->i] != '1' && draw->input[draw->i] != '0')
			draw->x += (draw->x_s * nb);
		if (draw->input[draw->i] != '1' && draw->input[draw->i] == '0')
			draw->x += draw->x_s;
		else if (draw->input[draw->i] == '\n')
		{
			draw->x = x;
			draw->y += draw->y_s;
		}
		draw->i += 1;
	}
}

void						draw_num(t_edit *edit, t_draw data, int num)
{
	t_draw					draw;

	draw.input = check_num(num);
	draw.x = data.x;
	draw.y = data.y;
	draw.y_s = data.y_s;
	draw.x_s = data.y_s;
	draw.color = check_color(data.color);
	draw_(edit, &draw);
}

void						draw_text(t_edit *edit)
{
	int						x;
	int						y;
	int						i;
	int						nb;

	i = 0;
	nb = 0;
	x = 600;
	y = HUD_BEGIN;
	if (edit->input_flag == 1)
	{
		while (edit->input_list[i] && edit->input_list[i] != ' ')
		{
			nb = edit->input_list[i] - 48;
			draw_num(edit, write_num(x += 20, 900, 1), nb);
			i++;
		}
		draw_num(edit, write_num(x += 15, 900, 4), 10);
	}
}

void			input_mode(t_input *in, t_edit *edit)
{
	int		minkey;
	int		maxkey;
	int		i;
	int		j;
	int		k;

	k = 0;
	minkey = 89;
	maxkey = 98;
	i = minkey;
	j = 0;
	if (in->key[SDL_SCANCODE_KP_ENTER] && edit->input_trigger == 1)
	{
		edit->input_cursor = 0;
		edit->input_res = ft_atoi(edit->input_list);
		handle_res(edit);
		while (k < 9)
		{
			edit->input_list[k] = 0;
			k++;
		}
		k = 0;
		in->key[SDL_SCANCODE_KP_ENTER] = SDL_FALSE;
	}
	if (in->key[SDL_SCANCODE_BACKSPACE])
	{
		edit->input_trigger = 0;
		if (edit->input_cursor != 0)
		{
			if (edit->input_list[edit->input_cursor - 1] != ' ')
			{
				edit->input_list[edit->input_cursor - 1] = ' ';
				edit->input_cursor--;
			}
		}
		edit->input_trigger = 1;
		in->key[SDL_SCANCODE_BACKSPACE] = SDL_FALSE;
	}
	while (i <= maxkey && edit->input_trigger == 1)
	{
		if (in->key[i])
		{
			if (i != 98)
				j = i - 88;
			else if (i == 98)
				j = 0;
			edit->input_flag = 1;
			if (edit->input_cursor != 9)
			{
				edit->input_list[edit->input_cursor] = (j + '0');
				edit->input_cursor++;
			}
			in->key[i] = SDL_FALSE;
			j = 0;
		}
		i++;
	}
}

void			check_input(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_T] && edit->hl_sec)
	{
		if (edit->hl_vert)
		{
			if (edit->hl_vert->next)
				edit->hl_vert->next->col = edit->hl_vert->next->oldcol;
			else
				edit->hl_sec->vert->col = edit->hl_sec->vert->oldcol;
		}
		edit->hl_vert = NULL;
		edit->input_flag = 1;
		edit->input_trigger = 1;
		in->key[SDL_SCANCODE_T] = SDL_FALSE;
	}
}
