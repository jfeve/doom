/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <jfeve@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:08:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:48:05 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				usage(void)
{
	ft_putendl("Usage : ./doom-nukem <file>\n\tor ./doom-nukem edit.");
	return (0);
}

int				init_edit(t_edit *edit)
{
	if (sdl_init(&edit->sdl) == 0)
		return (0);
	edit->err = 0;
	return (1);
}

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
			if (y % 10 == 0 || x % 10 == 0)
				edit->sdl.pix[y * WIN_W + x] = 0x00A200FF;
			x++;
		}
		y++;
	}
}

void			draw_vert(t_lis *tmp, t_edit *edit)
{
	int x;
	int y;

	x = tmp->x - 4;
	y = tmp->y - 4;
	while (x <= tmp->x + 4)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[(y + 8) * WIN_W + x] = WHITE;
		x++;
	}
	while (y <= tmp->y + 4)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[y * WIN_W + (x - 9)] = WHITE;
		y++;
	}
	edit->sdl.pix[tmp->y * WIN_W + tmp->x] = WHITE;
}

void			put_vert(t_lis *vert, t_edit *edit)
{
	t_lis		*tmp;

	tmp = vert;
	while (tmp != NULL)
	{
		draw_vert(tmp, edit);
		tmp = tmp->next;
	}
}

void			level_editor(void)
{
	t_lis		*vert;
	t_edit		edit;
	t_input		in;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&edit, sizeof(t_edit));
	vert = NULL;
	if (init_edit(&edit) == 0)
		return (ft_putendl("Init Edit Error"));
	while (!in.quit)
	{
		update_event(&in);
		check_event(&in, &vert);
		set_grid(&edit);
		put_vert(vert, &edit);
		if (display_frame(edit.sdl.ren, edit.sdl.pix) == 0)
		{
			free_sdl(&edit.sdl, 5);
			return ;
		}
		SDL_Delay(1000/60);
	}
	return ;
}

int				main(int argc, char **argv)
{
	if (argc != 2)
		return(usage());
	if (strcmp(argv[1], "edit") == 0)
		level_editor();
}
