/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_reader.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:06:11 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 17:14:25 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static int	read_mapfhead(int fd, t_mapf *mapf)
{
	read(fd, &mapf->magic, 4);
	mapf->magic[4] = '\0';
	if (ft_strcmp(mapf->magic, "MAP2") != 0)
	{
		ft_putendl("Error, the map file is not valid");
		return (0);
	}
	read(fd, &mapf->pl_x, sizeof(int));
	read(fd, &mapf->pl_y, sizeof(int));
	read(fd, &mapf->player.sect, sizeof(short));
	read(fd, &mapf->player.angle, sizeof(float));
	mapf->player.where.x = mapf->pl_x;
	mapf->player.where.y = mapf->pl_y;
	mapf->player.anglecos = cos(mapf->player.angle);
	mapf->player.anglecos = sin(mapf->player.angle);
	read(fd, &mapf->finish_x, sizeof(int));
	read(fd, &mapf->finish_y, sizeof(int));
	read(fd, &mapf->finish_sec, sizeof(short));
	read(fd, &mapf->nbsect, sizeof(int));
	read(fd, &mapf->diff, sizeof(short));
	return (1);
}

static int	check_access(void)
{
	if (access("map.tar", F_OK) == -1)
	{
		ft_putendl("The map archive doesn't exist");
		return (0);
	}
	return (1);
}

static int	untar(int *tmp)
{
	pid_t	child;
	char	*args[4];

	if (!check_access())
		return (0);
	args[0] = "/usr/bin/tar";
	args[1] = "-xf";
	args[2] = "./map.tar";
	args[3] = NULL;
	if ((child = fork()) == -1)
	{
		ft_putendl("fork() error");
		return (0);
	}
	if (child == 0)
	{
		execve("/usr/bin/tar", args, NULL);
		exit(EXIT_FAILURE);
	}
	else
		while (wait(tmp) != child)
			;
	return (1);
}

static int	opened(t_mapf *mapf, int fd)
{
	int		i;

	i = -1;
	if (!read_mapfhead(fd, mapf))
		return (0);
	if (!(mapf->sectors = malloc(sizeof(t_sector) * mapf->nbsect + 1)))
		return (0);
	while (++i != mapf->nbsect)
		if (!(read_sector(fd, mapf, i)))
		{
			free(mapf->sectors);
			return (0);
		}
	return (1);
}

int			read_map(t_mapf *mapf, char *mapname)
{
	int		fd;
	char	*mapfile;

	if (!untar(&fd))
		return (0);
	mapfile = ft_strjoin(MAP_PATH, mapname);
	if ((fd = open(mapfile, O_RDONLY)) != -1)
	{
		if (!opened(mapf, fd))
		{
			ft_strdel(&mapfile);
			close(fd);
			return (0);
		}
		mapf->player.where.z = (float)mapf->sectors[mapf->player.sect].floor
		+ (float)EYE;
		free(mapfile);
		close(fd);
		return (1);
	}
	else
	{
		ft_putendl("The map file does not exist");
		return (0);
	}
}
