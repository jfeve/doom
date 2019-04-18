/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:08:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 17:43:17 by nzenzela    ###    #+. /#+    ###.fr     */
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

void			init_content(t_edit *edit)
{
	edit->con = create_content();
	edit->con->x = WIN_W / 3;
	edit->con->y = 35;
	edit->con->display = 1;
	edit->con->cursor = 0;
	edit->con->trigger = 0;
	fill_str_content(256, edit->con->c_title, "level editor ");
	fill_str_content(2048, edit->con->c_content, "v1");
}

int				init_edit(t_edit *edit)
{
	init_content(edit);
	edit->player = NULL;
	edit->finish = NULL;
	edit->hl_sec = NULL;
	edit->hl_vert = NULL;
	edit->nbsect = 0;
	edit->hl = 0;
	edit->sect = 0;
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
	put_vert(edit, edit->vert);
	draw_obj_enem(edit);
	draw_vec(edit, *in);
	draw_sec(edit);
	if (edit->player)
		draw_vert(edit->player, edit);
	prepare_draw(edit);
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
	if (argc == 3 && strcmp(argv[1], "edit") == 0)
		level_editor(argv[2]);
	else
		return (usage());
}
