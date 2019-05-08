/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:08:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 22:25:01 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static int	usage(void)
{
	ft_putendl("Usage : ./doom-nukem <file>");
	ft_putendl("\tor ./doom-nukem edit <mapname>.");
	return (0);
}

int			init_content(t_edit *edit)
{
	edit->con = create_content();
	if (edit->con == NULL)
		return (0);
	edit->con->x = WIN_W / 2;
	edit->con->y = 35;
	edit->con->display = 0;
	edit->con->cursor = 0;
	edit->con->trigger = 1;
	fill_str_content(256, edit->con->c_title, "level editor ");
	fill_str_content(2048, edit->con->c_content, "v1");
	return (1);
}

int			choose_set(t_edit *edit)
{
	if (edit->hl_sec_temp)
	{
		if (edit->hl_sec_temp->floor == -1)
			return (1);
	}
	else if (edit->hl_sec)
		if (edit->hl_sec->floor == -1)
			return (1);
	return (0);
}

void		set_trigger(t_edit *edit, int choice, int trig)
{
	t_content	*tmp;
	char		*str;
	char		*title;

	tmp = edit->con;
	title = ft_strdup("\0");
	if (choice == 0)
		str = ft_strdup("set");
	else
		str = ft_strdup("not set");
	while (tmp)
	{
		if ((ft_strcmp(title, tmp->c_title) == 0) &&
				(ft_strcmp(str, tmp->c_content) == 0))
		{
			ft_strdel(&title);
			ft_strdel(&str);
			tmp->trigger = trig;
			return ;
		}
		tmp = tmp->next;
	}
	ft_strdel(&title);
	ft_strdel(&str);
}

int			main(int argc, char **argv)
{
	if (argc == 3 && ft_strcmp(argv[1], "edit") == 0)
		level_editor(argv[2]);
	else if (argc == 2 && ft_strcmp(argv[1], "edit") == 0)
		return (usage());
	else if (argc == 2)
		render(argv[1]);
	else
		return (usage());
	return (0);
}
