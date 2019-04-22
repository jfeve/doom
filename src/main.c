/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:08:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 21:54:41 by jfeve       ###    #+. /#+    ###.fr     */
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

int				init_content(t_edit *edit)
{
	edit->con = create_content();
	if (edit->con == NULL)
		return (0);
	edit->con->x = WIN_W / 3;
	edit->con->y = 35;
	edit->con->display = 0;
	edit->con->cursor = 0;
	edit->con->trigger = 1;
	fill_str_content(256, edit->con->c_title, "level editor ");
	fill_str_content(2048, edit->con->c_content, "v1");
	return (1);
}

int				get_update(t_edit *edit, t_input *in, char *mapname)
{
	clear_tab(&edit->sdl);
	update_event(in);
	if (check_event(mapname, in, edit) == 0)
		return (0);
	set_grid(edit);
	hud(edit);
	put_vert(edit, edit->vert);
	draw_obj_enem(edit);
	draw_vec(edit, *in);
	draw_sec(edit);
	if (edit->player)
		draw_vert(edit->player, edit);
	if (edit->finish)
		draw_vert(edit->finish, edit);
	prepare_draw(edit);
	return (1);
}

int				main(int argc, char **argv)
{
//	sleep(15);
	if (argc == 3 && ft_strcmp(argv[1], "edit") == 0)
		level_editor(argv[2]);
//	else if (argc == 2 && ft_strcmp(argv[1], "game") == 0)
//		render();
	else
		return (usage());
//	sleep(15);
	return (0);
}
