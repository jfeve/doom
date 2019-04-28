/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_reader.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:06:11 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 03:06:27 by jfeve       ###    #+. /#+    ###.fr     */
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
		mapf->objects = (t_objs *)malloc(
			sizeof(t_objs) * mapf->sectors[i].nbobjs);
		while (++iobjs < mapf->sectors[i].nbobjs)
			read_objs_data(fd, mapf, iobjs);
	}
	if (mapf->sectors[i].nbenem != 0)
	{
		mapf->enemies = (t_enemies *)malloc(
			sizeof(t_enemies) * mapf->sectors[i].nbenem);
		while (++ienem < mapf->sectors[i].nbenem)
			read_enem_data(fd, mapf, ienem);
	}
	return (1);
}

int				read_mapfhead(int fd, t_mapf *mapf, char *mapfile)
{
	read(fd, &mapf->magic, 4);
	mapf->magic[4] = '\0';
	if (ft_strcmp(mapf->magic, "MAP2") != 0)
	{
		ft_putendl("Error, the map file is not valid");
		free(mapfile);
		close(fd);
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
	int			fd;
	char		*mapfile;
	int			i;

	i = -1;
	mapfile = (char*)malloc(sizeof(char) *
		(int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
	ft_strcat(ft_strcat(ft_strcat(mapfile, MAP_PATH), mapname), ".mapf");
	if ((fd = open(mapfile, O_RDONLY)) != -1)
	{
		if (!read_mapfhead(fd, mapf, mapfile))
		{
			free (&mapfile);
			close (fd);
			return (0);
		}
		mapf->sectors = (t_sector *)malloc(sizeof(t_sector) * mapf->nbsect + 1);
		while (++i != mapf->nbsect)
			read_sector(fd, mapf, i);
		mapf->player.where.z = mapf->sectors[mapf->player.sect].floor + EYE;
		print_read(mapf);
		free(mapfile);
		close(fd);
		return (1);
	}
	else
	{
		dprintf(1, "\nThe map does not exist\n");
		return (0);
	}
}
