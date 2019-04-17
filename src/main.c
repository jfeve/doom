/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:08:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 16:31:36 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				usage(void)
{
	ft_putendl("Usage : ./doom-nukem <file>");
	ft_putendl("\tor ./doom-nukem edit <mapname>.");
	return (0);
}

int				init_edit(t_edit *edit)
{
	edit->hud_flag = 0;
	edit->input_flag = 0;
	edit->input_cursor = 0;
	edit->player = NULL;
	edit->input_trigger = 0;
	edit->hl_sec = NULL;
	edit->hl_vert = NULL;
	edit->nbsect = 0;
	edit->hl = 0;
	edit->sect = 0;
	while (edit->input_list[edit->input_cursor])
	{
		dprintf(1, "%c", edit->input_list[edit->input_cursor++]);
		edit->input_list[edit->input_cursor++] = ' ';
	}
	edit->input_cursor = 0;
	if (sdl_init(&edit->sdl) == 0)
		return (0);
	edit->err = 0;
	edit->vert = NULL;
	edit->sect = NULL;
	return (1);
}

void			get_update(t_edit *edit, t_input *in, char *mapname)
{
	clear_tab(&edit->sdl);
	update_event(in);
	check_event(mapname, in, edit);
	set_grid(edit);
	hud(edit);
	draw_text(edit);
	put_vert(edit, edit->vert);
	draw_obj_enem(edit);
	draw_vec(edit, *in);
	draw_sec(edit);
	if (edit->player)
		draw_vert(edit->player, edit);
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
		get_update(&edit, &in, mapname);
		if (display_frame(edit.sdl.ren, edit.sdl.pix) == 0)
		{
			free_sdl(&edit.sdl, 5);
			return ;
		}
		SDL_Delay(1000 / 60);
	}
	return ;
}

int				main(int argc, char **argv)
{
	if (argc == 3 && ft_strcmp(argv[1], "edit") == 0)
		level_editor(argv[2]);
//	else if (argc == 2 && ft_strcmp(argv[1], "game") == 0)
//		render();
	else
		return (usage());
}
