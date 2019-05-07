/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_reader.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:06:11 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 17:45:01 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				read_entities(int fd, t_mapf *mapf, int i)
{
	int			ienem;
	int			iobjs;

	iobjs = -1;
	ienem = -1;
	if (mapf->sectors[i].nbobjs != 0)
	{
	dprintf(1, "mapf->sectors[i].nbobjs = %d\n", mapf->sectors[i].nbobjs);
		mapf->sectors[i].obj = (t_objs *)malloc(
			sizeof(t_objs) * mapf->sectors[i].nbobjs);
		while (++iobjs < mapf->sectors[i].nbobjs)
			read_objs_data(fd, mapf, iobjs, i);
	}
	else
		mapf->sectors[i].obj = NULL;
	if (mapf->sectors[i].nbenem != 0)
	{
		mapf->sectors[i].enem = (t_enemies *)malloc(
			sizeof(t_enemies) * mapf->sectors[i].nbenem);
		while (++ienem < mapf->sectors[i].nbenem)
			read_enem_data(fd, mapf, ienem, i);
	}
	else
		mapf->sectors[i].enem = NULL;
	return (1);
}

int				read_mapfhead(int fd, t_mapf *mapf)
{
	read(fd, &mapf->magic, 4);
	mapf->magic[4] = '\0';
	if (ft_strcmp(mapf->magic, "MAP2") != 0)
	{
		ft_putendl("Error, the map file is not valid");
		//free(mapfile);
		//close(fd);
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

int				read_sector(int fd, t_mapf *mapf, int i)
{
	int		k;

	mapf->nbobjs = 0;
	mapf->nbenem = 0;
	read(fd, &mapf->sectors[i].gravity, sizeof(short));
	read(fd, &mapf->sectors[i].floor, sizeof(short));
	read(fd, &mapf->sectors[i].ceil, sizeof(short));
	read(fd, &mapf->sectors[i].nbvert, sizeof(int));
	read(fd, &mapf->sectors[i].nbobjs, sizeof(int));
	read(fd, &mapf->sectors[i].nbenem, sizeof(int));
	mapf->nbobjs += mapf->sectors[i].nbobjs;
	mapf->nbenem += mapf->sectors[i].nbenem;
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
	read_entities(fd, mapf, i);
	return (1);
}

int				read_map(t_mapf *mapf, char *mapname)
{
	int		fd;
	char	*mapfile;
	int		i;
	pid_t	child;
	char	*args[3];

	if (access("map.tar", F_OK) == -1)
	{
		ft_putendl("The map archive doesn't exist");
		return (0);
	}
	if ((child = fork()) == -1)
	{
		ft_putendl("fork() error");
		return (0);
	}
	args[0] = "/usr/bin/tar";
	args[1] = "map.tar";
	args[2] = NULL;
	if (child == 0)
	{
		execve("/usr/bin/tar", args, NULL);
		exit(EXIT_SUCCESS);
	}
	else
		while (wait(&i) != child) ;
	i = -1;
	mapfile = ft_strjoin(MAP_PATH, mapname);
	dprintf(1, "%s\n", mapfile);
	if ((fd = open(mapfile, O_RDONLY)) != -1)
	{
		if (!read_mapfhead(fd, mapf))
		{
			ft_strdel(&mapfile);
			close (fd);
			return (0);
		}
		mapf->sectors = (t_sector *)malloc(sizeof(t_sector) * mapf->nbsect + 1);
		while (++i != mapf->nbsect)
			read_sector(fd, mapf, i);
		mapf->player.where.z = (float)mapf->sectors[mapf->player.sect].floor + (float)EYE;
		print_read(mapf);
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
