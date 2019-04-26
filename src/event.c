/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:16:42 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 19:42:33 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"
#include "../incs/mapf.h"

void			update_event(t_input *in)
{
	while (SDL_PollEvent(&in->event))
	{
		if (in->event.type == SDL_QUIT)
			in->quit = SDL_TRUE;
		else if (in->event.type == SDL_KEYDOWN)
			in->key[in->event.key.keysym.scancode] = SDL_TRUE;
		else if (in->event.type == SDL_KEYUP)
			in->key[in->event.key.keysym.scancode] = SDL_FALSE;
		else if (in->event.type == SDL_MOUSEMOTION)
		{
			in->x = in->event.motion.x;
			in->y = in->event.motion.y;
			in->xrel = in->event.motion.xrel;
			in->yrel = in->event.motion.yrel;
		}
		else if (in->event.type == SDL_MOUSEWHEEL)
		{
			in->xwheel = in->event.wheel.x;
			in->ywheel = in->event.wheel.y;
		}
		else if (in->event.type == SDL_MOUSEBUTTONDOWN)
			in->mouse[in->event.button.button] = SDL_TRUE;
		else if (in->event.type == SDL_MOUSEBUTTONUP)
			in->mouse[in->event.button.button] = SDL_FALSE;
	}
}

int				click_vert(t_input *in, t_edit *edit)
{
	if (in->mouse[SDL_BUTTON_LEFT] && in->y < HUD_BEGIN && edit->hl == 0)
	{
		edit->hud_flag = 1;
		if (edit->vert == NULL)
		{
			edit->vert = create_vert(in->x, in->y);
			if (edit->vert == NULL)
				return (0);
		}
		else
		{
			if (add_vert(in->x, in->y, edit, edit->vert) == -1)
				return (0);
		}
		in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
	}
	return (1);
}

void			settings_event(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_R])
	{
		edit->nbsect = 0;
		edit->err = 0;
		edit->hud_flag = 0;
		edit->hl_sec = NULL;
		edit->hl_vert = NULL;
		edit->nbsect = 0;
		edit->sec = 0;
		edit->hl = 0;
		if (edit->vert)
			free_lis(&edit->vert);
		if (edit->player)
			free_lis(&edit->player);
		if (edit->finish)
			free_lis(&edit->finish);
		if (edit->sect)
			free_sec(&edit->sect);
	}
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
}

void			read_head(int fd, t_mapf *mapf)
{
	read(fd, &mapf->pl_x, sizeof(int));
	read(fd, &mapf->pl_y, sizeof(int));
	read(fd, &mapf->pl_sec, sizeof(short));
	read(fd, &mapf->finish_x, sizeof(int));
	read(fd, &mapf->finish_y, sizeof(int));
	read(fd, &mapf->finish_sec, sizeof(short));
	read(fd, &mapf->nbsect, sizeof(int));
}

void			read_map(t_mapf *mapf, char *mapname)
{
	int			fd;
	char		*mapfile;
	int			i;
	int			k;

	i = 0;
	mapfile = (char*)malloc(sizeof(char) *
		(int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
	ft_strcat(ft_strcat(ft_strcat(mapfile, MAP_PATH), mapname), ".mapf");
	if ((fd = open(mapfile, O_RDONLY)) != -1)
	{
		read(fd, &mapf->magic, 4);
		mapf->magic[4] = '\0';
		if (ft_strcmp(mapf->magic, "MAPF") != 0)
		{
			ft_putendl("Error, the map file is not valid");
			free(mapfile);
			close(fd);
			return ;
		}
		dprintf(1, "\n------------Data Read----------\n");
		read(fd, &mapf->pl_x, sizeof(int));
		read(fd, &mapf->pl_y, sizeof(int));
		read(fd, &mapf->pl_sec, sizeof(short));
		read(fd, &mapf->finish_x, sizeof(int));
		read(fd, &mapf->finish_y, sizeof(int));
		read(fd, &mapf->finish_sec, sizeof(short));
		read(fd, &mapf->nbsect, sizeof(int));
		mapf->sectors = (t_sector *)malloc(sizeof(t_sector) * mapf->nbsect + 1);
		while (i != mapf->nbsect)
		{
			read(fd, &mapf->sectors[i].floor, sizeof(short));
			read(fd, &mapf->sectors[i].ceil, sizeof(short));
			read(fd, &mapf->sectors[i].nbvert, sizeof(int));
			mapf->sectors[i].vert =
				(t_vertex *)malloc(sizeof(t_vertex) * mapf->sectors[i].nbvert);
			k = 0;
			while (k != mapf->sectors[i].nbvert)
			{
				read(fd, &mapf->sectors[i].vert[k].x, sizeof(int));
				read(fd, &mapf->sectors[i].vert[k].y, sizeof(int));
				read(fd, &mapf->sectors[i].vert[k].text, sizeof(short));
				read(fd, &mapf->sectors[i].vert[k].neigh, sizeof(int));
				k++;
			}
			i++;
		}
		dprintf(1, "Header : %s\n", mapf->magic);
		dprintf(1, "Player : x = %d\n", mapf->pl_x);
		dprintf(1, "Player : y = %d\n", mapf->pl_y);
		dprintf(1, "Player : Sector = %d\n", mapf->pl_sec);
		dprintf(1, "Finish : x = %d\n", mapf->finish_x);
		dprintf(1, "Finish : y = %d\n", mapf->finish_y);
		dprintf(1, "Finish : Sector = %d\n", mapf->finish_sec);
		dprintf(1, "Nb sector : %d\n", mapf->nbsect);
		dprintf(1, "Num of Bits : %lu\n", (sizeof(int) + sizeof(int)
						+ sizeof(short) + sizeof(int) + sizeof(int)
							+ sizeof(short) + sizeof(int)));
		dprintf(1, "\n--------\n");
		i = 0;
		k = 0;
		while (i < mapf->nbsect)
		{
			dprintf(1, "Sector : %d\n", i);
			dprintf(1, " Floor : %d\n", mapf->sectors[i].floor);
			dprintf(1, " Ceil : %d\n", mapf->sectors[i].ceil);
			dprintf(1, " Nb Vertex %d\n", mapf->sectors[i].nbvert);
			k = 0;
			while (k < mapf->sectors[i].nbvert)
			{
				dprintf(1, "   X : %d\n", mapf->sectors[i].vert[k].x);
				dprintf(1, "   Y : %d\n", mapf->sectors[i].vert[k].y);
				dprintf(1, "   Texture : %d\n", mapf->sectors[i].vert[k].text);
				dprintf(1, "   Voisins : %d\n", mapf->sectors[i].vert[k].neigh);
				k++;
			}
			i++;
		}
		dprintf(1, "\n------------End Read----------\n");
		close(fd);
	}
	else
	{
		dprintf(1, "\nThe map does not exist\n");
		return ;
	}
	return ;
}

int				check_event(char *mapname, t_input *in, t_edit *edit)
{
	t_mapf		mapf;

	if (in->key[SDL_SCANCODE_K] && edit->hl_sec && edit->dyn_trigger != 1)
	{
		edit->err = 2;
		in->key[SDL_SCANCODE_K] = SDL_FALSE;
	}
	print_info(edit, in);
	settings_event(edit, in);
	cancels(edit, in);
	if (click_vert(in, edit) == 0)
		return (0);
	hl_mode(in, edit);
	hl_vec(edit, in);
	if (new_vert(edit, in) == 0)
		return (0);
	portals(edit, in);
	if (check_input(edit, in) == 0)
		return (0);
	dyn_input(edit, in);
	if (enem(edit, in) == 0)
		return (0);
	if (obj(edit, in) == 0)
		return (0);
	if (create_player(edit, in) == 0)
		return (0);
	if (create_finish(edit, in) == 0)
		return (0);
	save_map(in, mapname, edit);
	if (in->key[SDL_SCANCODE_L])
	{
		in->key[SDL_SCANCODE_L] = SDL_FALSE;
		read_map(&mapf, mapname);
	}
	return (1);
}
