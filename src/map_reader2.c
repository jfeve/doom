/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_reader2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:08:27 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 21:41:45 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	read_enem_data(int fd, t_mapf *mapf, int ienem, int i)
{
	int		plx;
	int		ply;

	read(fd, &plx, sizeof(int));
	mapf->sectors[i].enem[ienem].x = (float)plx;
	read(fd, &ply, sizeof(int));
	mapf->sectors[i].enem[ienem].y = (float)ply;
	read(fd, &mapf->sectors[i].enem[ienem].type, sizeof(short));
	mapf->sectors[i].enem[ienem].sec = i;
	mapf->sectors[i].enem[ienem].life = 100;
}

static void	read_objs_data(int fd, t_mapf *mapf, int iobjs, int i)
{
	read(fd, &mapf->sectors[i].obj[iobjs].x, sizeof(int));
	read(fd, &mapf->sectors[i].obj[iobjs].y, sizeof(int));
	read(fd, &mapf->sectors[i].obj[iobjs].type, sizeof(short));
	mapf->sectors[i].obj[iobjs].picked = 0;
	mapf->sectors[i].obj[iobjs].sec = i;
}

int			open_error(char **mapfile)
{
	ft_putendl("We could not open the file");
	free(*mapfile);
	return (0);
}

static int	read_enemies(t_mapf *mapf, int fd, int i)
{
	int		ienem;

	ienem = -1;
	if (mapf->sectors[i].nbenem != 0)
	{
		if (!(mapf->sectors[i].enem = malloc(sizeof(t_enemies)
		* mapf->sectors[i].nbenem)))
		{
			free(mapf->sectors[i].obj);
			return (0);
		}
		while (++ienem < mapf->sectors[i].nbenem)
			read_enem_data(fd, mapf, ienem, i);
	}
	else
		mapf->sectors[i].enem = NULL;
	return (1);
}

int			read_entities(int fd, t_mapf *mapf, int i)
{
	int			iobjs;

	iobjs = -1;
	if (mapf->sectors[i].nbobjs != 0)
	{
		if (!(mapf->sectors[i].obj = malloc(sizeof(t_objs)
		* mapf->sectors[i].nbobjs)))
			return (0);
		while (++iobjs < mapf->sectors[i].nbobjs)
			read_objs_data(fd, mapf, iobjs, i);
	}
	else
		mapf->sectors[i].obj = NULL;
	if (!read_enemies(mapf, fd, i))
		return (0);
	return (1);
}
