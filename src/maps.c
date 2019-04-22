/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 16:24:01 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static	int				putinfo_head(int fd, t_edit *edit)
{
	if (fd == -1)
		return (0);
	write(fd, "MAPF", 4);
	if (edit->nbsect != 0)
	{
		if (edit->sec)
		{
			write(fd, &edit->player->x, sizeof(int));
			write(fd, &edit->player->y, sizeof(int));
			write(fd, &edit->player->text, sizeof(short));
			write(fd, &edit->finish->x, sizeof(int));
			write(fd, &edit->finish->y, sizeof(int));
			write(fd, &edit->finish->text, sizeof(short));
			write(fd, &edit->nbsect, sizeof(int));
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

	if (fd == -1)
		return (0);
	tmp = edit->sect;
	while (tmp != NULL)
	{
		temp = tmp->vert;
		while (temp != NULL)
		{
			write(fd, &temp->x, sizeof(int));
			write(fd, &temp->y, sizeof(int));
			write(fd, &temp->text, sizeof(short));
			temp = temp->next;
		}
		free(temp);

		temp = tmp->enem;
		while (temp != NULL)
		{
			write(fd, &temp->x, sizeof(int));
			write(fd, &temp->y, sizeof(int));
			write(fd, &temp->text, sizeof(short));
			temp = temp->next;
		}
		free(temp);
		temp = tmp->obj;
		while (temp != NULL)
		{
			write(fd, &temp->x, sizeof(int));
			write(fd, &temp->y, sizeof(int));
			write(fd, &temp->text, sizeof(short));
			temp = temp->next;
		}
		free(temp);
		write(fd, &tmp->floor, sizeof(short));
		write(fd, &tmp->ceil, sizeof(short));
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

int						save_error(char **mapfile)
{
	ft_putendl("There is no sector, map not saved");
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
			putinfo_head(fd, edit);
			putinfo_sector(fd, edit);
			close(fd);
			return (1);
		}
		else
		{
			save_error(&mapfile);
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
