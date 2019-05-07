/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 16:22:48 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static	int				putinfo_head(int fd, t_edit *edit)
{
	float			angle;

	angle = 0.5;
	if (fd == -1)
		return (0);
	if (edit->nbsect != 0 && mcheck_pos(edit))
	{
		if (edit->sect)
		{
			write(fd, "MAP2", 4);
			write(fd, &edit->player->x, sizeof(int));
			write(fd, &edit->player->y, sizeof(int));
			write(fd, &edit->player->text, sizeof(short));
			write(fd, &angle, sizeof(float));
			write(fd, &edit->finish->x, sizeof(int));
			write(fd, &edit->finish->y, sizeof(int));
			write(fd, &edit->finish->text, sizeof(short));
			write(fd, &edit->nbsect, sizeof(int));
			write(fd, &edit->diff, sizeof(short));
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
		if (tmp->floor == -1 && tmp->ceil == -1)
			return (err_map("A sector has some unset data", temp));
		temp = tmp->vert;
		write(fd, &tmp->gravity, sizeof(short));
		write(fd, &tmp->floor, sizeof(short));
		write(fd, &tmp->ceil, sizeof(short));
		write(fd, &tmp->nbvert, sizeof(int));
		write(fd, &tmp->objscount, sizeof(int));
		write(fd, &tmp->enemcount, sizeof(int));
		putinfo_sec(fd, temp, tmp);
		tmp = tmp->next;
	}
	free(tmp);
	return (1);
}

int						put_data(int fd, t_edit *edit)
{
	if (putinfo_head(fd, edit))
	{
		if (putinfo_sector(fd, edit))
			return (1);
		else
		{
			save_error();
			close(fd);
			return (0);
		}
	}
	else
	{
		save_error();
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int						map_writer(char *mapname, t_edit *edit)
{
	int					fd;
	char				*mapfile;

//	mapfile = (char*)malloc(sizeof(char) *
//		(int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
//	ft_strcat(ft_strcat(ft_strcat(mapfile, MAP_PATH), mapname), ".mapf");
	mapfile = ft_strjoin(MAP_PATH, mapname);
	if ((fd = open(mapfile, O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU)) != -1)
	{
		if (edit->nbsect != 0)
			return (put_data(fd, edit));
		else
		{
			save_error();
			close(fd);
			return (0);
		}
	}
	else
		return (open_error(&mapfile));
}

int						save_map(t_input *in, char *mapname, t_edit *edit)
{
	pid_t	child;
	int		tmp;
	char	*args[5];

	if (in->key[SDL_SCANCODE_S])
	{
		if (map_writer(mapname, edit))
		{
			args[0] = "/usr/bin/tar";
			args[1] = "-cf";
			args[2] = "map.tar";
			args[3] = "data/";
			args[4] = NULL;
			if ((child = fork()) == -1)
			{
				ft_putendl("fork() error");
				return (0);
			}
			if (child == 0)
			{
				execve("/usr/bin/tar", args, NULL);
				exit(EXIT_SUCCESS);
			}
			else
				while (wait(&tmp) != child) ;
			ft_putendl("\n--------Map saved--------\n\n");
			return (1);
		}
		else
		{
			ft_putendl("\n--------Map not saved--------\n\n");
			return (0);
		}
		in->key[SDL_SCANCODE_S] = SDL_FALSE;
	}
	return (0);
}
