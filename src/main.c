/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:08:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 15:25:41 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				usage(void)
{
	ft_putendl("Usage : ./doom-nukem <file>\n\tor ./doom-nukem edit <mapname>.");
	return (0);
}

int				init_edit(t_edit *edit)
{
	if (sdl_init(&edit->sdl) == 0)
		return (0);
	edit->err = 0;
	edit->vert = NULL;
	edit->sect = NULL;
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
			if (y % UNIT == 0 || x % UNIT == 0)
				edit->sdl.pix[y * WIN_W + x] = CYAN;
			x++;
		}
		y++;
	}
}

t_lis			mult_unit(t_lis vert)
{
	t_lis	a;
	a.x = vert.x * UNIT;
	a.y = vert.y * UNIT;
	a.col = vert.col;
	return (a);
}

void			draw_vec(t_edit *edit, t_input in)
{
	t_lis *tmp;
	t_lis point;

	if (edit->vert == NULL)
		return ;
	tmp = edit->vert;
	while (tmp->next != NULL)
	{
		bresen(mult_unit(*tmp), mult_unit(*tmp->next), &edit->sdl);
		tmp =tmp->next;
	}
	if (edit->oldvert != NULL)
	{
		bresen(mult_unit(*tmp), mult_unit(*edit->oldvert), &edit->sdl);
		set_sect(edit);
	}
	else
	{
		point.x = arr(in.x);
		point.y = arr(in.y);
		point.col = WHITE;
		bresen(mult_unit(*tmp), mult_unit(point), &edit->sdl);
	}
}

int				check_mapname(char *mapname)
{
	int		i;

	i = 0;
	if (ft_strlen(mapname) >= 4)
	{
		while (mapname[i])
			if (ft_isalpha(mapname[i]))
				i++;
		if (i != ((int)ft_strlen(mapname)))
			return (0);
		else
			return (1);
	}
	else
		return (0);
	return (1);
}

void			level_editor(char *mapname)
{
	t_edit		edit;
	t_input		in;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&edit, sizeof(t_edit));
	if (init_edit(&edit) == 0)
		return (ft_putendl("Init Edit Error"));
	if (!check_mapname(mapname))
		return (ft_putendl("Map name not valid"));
	while (!in.quit)
	{
		clear_tab(&edit.sdl);
		update_event(&in);
		check_event(mapname, &in, &edit);
		set_grid(&edit);
		hud(&edit);
		put_vert(&edit);
		draw_vec(&edit, in);
		draw_sec(&edit);
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
	// if (argc == 3 && strcmp(argv[1], "test") == 0 && ft_strlen(argv[2]) > 2)
		// map_writer(argv[2]);
	if (argc == 3 && strcmp(argv[1], "edit") == 0)
		level_editor(argv[2]);
	else
		return(usage());
}
