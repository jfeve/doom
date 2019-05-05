/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 13:29:31 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static int	putinfo_head(int fd, t_edit *edit)
{
	float	angle;

	angle = 0.5;
	if (mcheck_pos(edit) && edit->sect)
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
		return (1);
	}
	return (0);
}

static int	putinfo_sector(int fd, t_edit *edit)
{
	t_sec	*sect;

	sect = edit->sect;
	while (sect != NULL)
	{
		if (sect->floor == -1 || sect->ceil == -1)		//pas sur pour le ||
			return (unset_map(sect->id));
		write(fd, &sect->gravity, sizeof(short));
		write(fd, &sect->floor, sizeof(short));
		write(fd, &sect->ceil, sizeof(short));
		write(fd, &sect->nbvert, sizeof(int));
		write(fd, &sect->objscount, sizeof(int));
		write(fd, &sect->enemcount, sizeof(int));
		putinfo_sec(fd, sect);
		sect = sect->next;
	}
	return (1);
}

static int	put_data(int fd, t_edit *edit)
{
	if (putinfo_head(fd, edit))
	{
		if (putinfo_sector(fd, edit))
			return (1);
		else
		{
			ft_putendl("There has been an error while saving the file");
			close(fd);
			return (0);
		}
	}
	ft_putendl("Error while saving the file ; player or ending missing.");
	close(fd);
	return (0);
}

static int	map_writer(char *mapname, t_edit *edit)
{
	int		fd;
	char	*mapfile;

	if (!(mapfile = ft_strjoin(MAP_PATH, mapname)))
	{
		ft_putendl("Map name error");
		return (0);
	}
	if ((fd = open(mapfile, O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU)) == -1)
		return (open_error(&mapfile));
	if (edit->nbsect != 0)
	{
		if (put_data(fd, edit))
			return (1);
		else
		{
			ft_strdel(&mapfile);
			return (0);
		}
	}
	close(fd);
	ft_strdel(&mapfile);
	ft_putendl("Error while saving the file ; no sector was drawn.");
	return (0);
}

int			save_map(t_input *in, char *mapname, t_edit *edit)
{
	if (in->key[SDL_SCANCODE_S])
	{
		if (map_writer(mapname, edit))
		{
			ft_putendl("--------Map saved--------\n");
			return (1);
		}
		else
		{
			ft_putendl("Error saving the map.");
			return (0);
		}
		in->key[SDL_SCANCODE_S] = SDL_FALSE;
	}
	return (0);
}
