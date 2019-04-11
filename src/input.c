/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 16:32:55 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 18:41:51 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

t_draw							write_num(int x, int y,int col)
{
	t_draw	data;

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

void						draw_square(t_edit *edit, t_draw *draw)
{
	int i = draw->x;
	int j = draw->y;

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
	int		x;
	int		nb;

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

void						draw_num(t_edit *edit,t_draw data, int num)
{
	t_draw	draw;

	draw.input = check_num(num);
	draw.x = data.x;
	draw.y = data.y;
	draw.y_s = data.y_s;
	draw.x_s = data.y_s;
	draw.color = check_color(data.color);
	draw_(edit, &draw);
}


void			draw_text(t_edit *edit)
{
	int x;
	int y;

	x = TEXT_INPUT;
	y = HUD_BEGIN;
	if (edit->input_flag == 1)
	{
		draw_num(edit, write_num(600, 900, 1), 0);
		draw_num(edit, write_num(650, 900, 1), 1);
		draw_num(edit, write_num(690, 900, 1), 2);
		draw_num(edit, write_num(725, 900, 1), 3);
		draw_num(edit, write_num(765, 900, 1), 4);
		draw_num(edit, write_num(800, 900, 1), 5);
		draw_num(edit, write_num(840, 900, 1), 6);
		draw_num(edit, write_num(845, 900, 4), 10);
		draw_num(edit, write_num(845, 880, 4), 11);
		draw_num(edit, write_num(885, 880, 4), 12);
		draw_num(edit, write_num(880, 900, 1), 7);
		draw_num(edit, write_num(920, 900, 1), 8);
		draw_num(edit, write_num(970, 900, 1), 9);
	}
}

void			input_mode(t_input *in, t_edit *edit)
{
	int		minkey;
	int		maxkey;

	maxkey = 98;
	minkey = 89;
	if (in->key[SDL_SCANCODE_T])
	{
		edit->input_flag = 1;
		in->key[SDL_SCANCODE_T] = SDL_FALSE;
	}
	// if (in->key[SDL_SCANCODE_KP_1])
	// {
	// 	edit->input_flag = 1;
	// 	in->key[SDL_SCANCODE_KP_1] = SDL_FALSE;
	// }
	// if (in->key[SDL_SCANCODE_KP_2])
	// {
	// 	edit->input_flag = 1;
	// 	in->key[SDL_SCANCODE_KP_2] = SDL_FALSE;
	// }
	// if (in->key[SDL_SCANCODE_KP_3])
	// {
	// 	edit->input_flag = 1;
	// 	in->key[SDL_SCANCODE_KP_3] = SDL_FALSE;
	// }
	// if (in->key[SDL_SCANCODE_KP_9])
	// {
	// 	edit->input_flag = 1;
	// 	in->key[SDL_SCANCODE_KP_4] = SDL_FALSE;
	// }
	// if (in->key[SDL_SCANCODE_KP_4])
	// {
	// 	edit->input_flag = 1;
	// 	in->key[SDL_SCANCODE_KP_5] = SDL_FALSE;
	// }
	// if (in->key[SDL_SCANCODE_KP_5])
	// {
	// 	edit->input_flag = 1;
	// 	in->key[SDL_SCANCODE_KP_9] = SDL_FALSE;
	// }
	// if (in->key[SDL_SCANCODE_KP_9])
	// {
	// 	edit->input_flag = 1;
	// 	in->key[SDL_SCANCODE_KP_9] = SDL_FALSE;
	// }
}