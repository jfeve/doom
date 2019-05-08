/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_reader3.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 21:37:40 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 21:41:14 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	read_sect_data(t_mapf *mapf, int fd, int i)
{
	read(fd, &mapf->sectors[i].gravity, sizeof(short));
	read(fd, &mapf->sectors[i].floor, sizeof(short));
	read(fd, &mapf->sectors[i].ceil, sizeof(short));
	read(fd, &mapf->sectors[i].nbvert, sizeof(int));
	read(fd, &mapf->sectors[i].nbobjs, sizeof(int));
	read(fd, &mapf->sectors[i].nbenem, sizeof(int));
}

int			read_sector(int fd, t_mapf *mapf, int i)
{
	int		k;

	mapf->nbobjs = 0;
	mapf->nbenem = 0;
	read_sect_data(mapf, fd, i);
	mapf->nbobjs += mapf->sectors[i].nbobjs;
	mapf->nbenem += mapf->sectors[i].nbenem;
	if (!(mapf->sectors[i].vert = malloc(sizeof(t_vertex)
	* mapf->sectors[i].nbvert)))
		return (0);
	k = 0;
	while (k != mapf->sectors[i].nbvert)
	{
		read(fd, &mapf->sectors[i].vert[k].x, sizeof(int));
		read(fd, &mapf->sectors[i].vert[k].y, sizeof(int));
		read(fd, &mapf->sectors[i].vert[k].text, sizeof(short));
		read(fd, &mapf->sectors[i].vert[k].neigh, sizeof(int));
		k++;
	}
	if (!(read_entities(fd, mapf, i)))
	{
		free(mapf->sectors[i].vert);
		return (0);
	}
	return (1);
}
