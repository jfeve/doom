/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:19:21 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static	int				putinfo_head(int fd, t_edit *edit,
		unsigned short count_sect)
{
	float				player_pos_x;
	float				player_pos_y;
	unsigned short		player_pos_s;

	player_pos_x = 5.0;
	player_pos_y = 15.0;
	player_pos_s = 0;
	if (fd == -1)
		return (0);
	write(fd, "MAPF", 4);
	if (count_sect != 0)
	{
		if (edit->sec)
		{
			write(fd, &player_pos_x, sizeof(float));
			write(fd, &player_pos_y, sizeof(float));
			write(fd, &player_pos_s, sizeof(unsigned short));
			write(fd, &count_sect, sizeof(unsigned short));
		}
		return (1);
	}
	else
		return (0);
}

static	int				putinfo_sector(int fd, t_edit *edit)
{
	t_sec				*tmp;
	t_lis				*temp;
	int					i;
	int					sect;

	sect = 1;
	i = 1;
	if (fd == -1)
		return (0);
	tmp = edit->sect;
	while (tmp != NULL)
	{
		temp = tmp->vert;
		while (temp != NULL)
		{
			temp = temp->next;
			i += 1;
		}
		i = 1;
		sect += 1;
		tmp = tmp->next;
	}
	return (1);
}

int						open_error(char **mapfile)
{
	ft_putendl("We could not open the file");
	free(mapfile);
	return (0);
}

int						map_writer(char *mapname, t_edit *edit)
{
	int					fd;
	char				*mapfile;

	mapfile = (char*)malloc(sizeof(char) *
		(int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
	ft_strcat(ft_strcat(ft_strcat(mapfile, MAP_PATH), mapname), ".mapf");
	if ((fd = open(mapfile, O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU)) != -1)
	{
		if (edit->nbsect != 0)
		{
			putinfo_head(fd, edit, edit->nbsect);
			putinfo_sector(fd, edit);
			close(fd);
			return (1);
		}
		else
		{
			free(mapfile);
			close(fd);
			return (0);
		}
	}
	else
		return (open_error(&mapfile));
}

int						save_map(t_input *in, char *mapname, t_edit *edit)
{
	if (in->key[SDL_SCANCODE_S])
	{
		if (map_writer(mapname, edit))
			write(1, "\n-------Map sauver-------\n", 27);
		else
			write(1, "\n--------Map not saved-------\n", 30);
		in->key[SDL_SCANCODE_S] = SDL_FALSE;
	}
	return (0);
}
