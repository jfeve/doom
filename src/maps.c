/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 14:08:50 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static	int				putinfo_head(int fd, t_edit *edit)
{
	if (fd == -1)
		return (0);
	if (edit->nbsect != 0 && mcheck_pos(edit))
	{
		if (edit->sec)
		{
			write(fd, "MAPF", 4);
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

int						save_d(int fd, t_lis *temp)
{
	while (temp != NULL)
	{
		if (!mcheck_d(temp))
			return (err_map("some vectors in a sector is not set properly", temp));
		write(fd, &temp->x, sizeof(int));
		write(fd, &temp->y, sizeof(int));
		write(fd, &temp->text, sizeof(short));
		temp = temp->next;
	}
	free(temp);
	return (1);
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
		if ((temp = tmp->vert))
			putinfo_sec(fd, temp, tmp);
		else
			return (save_error2("Error while saving the Vertex", temp));
		if (!mcheck_sec(tmp))
			return (err_map("A sector has some unset data", temp));
		write(fd, &tmp->floor, sizeof(short));
		write(fd, &tmp->ceil, sizeof(short));
		tmp = tmp->next;
	}
	return (1);
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
			if (putinfo_head(fd, edit))
				if (putinfo_sector(fd, edit))
					return (1);
				else
				{
					save_error(mapfile);
					close(fd);
					return (0);
				}
			else
			{
				save_error(mapfile);
				close(fd);
				return (0);
			}
			close(fd);
			return (1);
		}
		else
		{
			save_error(mapfile);
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
