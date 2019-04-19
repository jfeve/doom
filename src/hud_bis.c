/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hud_bis.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 18:20:00 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 18:20:10 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			set_grid(t_edit *edit)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y % UNIT == 0 || x % UNIT == 0)
				edit->sdl.pix[y * WIN_W + x] = CYAN;
			x++;
		}
		y++;
	}
}

void			hud_hl(t_edit *edit)
{
	t_content	*con;

	con = edit->con;
	while (ft_strcmp(con->c_title, HL_SET_TUTO) != 0 && con)
	{
		if (ft_strcmp(con->c_title, TUTO) == 0)
			con->trigger = 0;
		con = con->next;
	}
	con->trigger = 1;
}
