/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_reader2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:08:27 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 21:37:19 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				read_enem_data(int fd, t_mapf *mapf, int ienem, int i)
{
	int		plx;
	int		ply;

	read(fd, &plx, sizeof(int));
	mapf->sectors[i].enem[ienem].x = (float)plx;
	read(fd, &ply, sizeof(int));
	mapf->sectors[i].enem[ienem].y = (float)ply;
	read(fd, &mapf->sectors[i].enem[ienem].type, sizeof(short));
	mapf->sectors[i].enem[ienem].sec = i;
	return (1);
}

int				read_objs_data(int fd, t_mapf *mapf, int iobjs, int i)
{
	read(fd, &mapf->sectors[i].obj[iobjs].x, sizeof(int));
	read(fd, &mapf->sectors[i].obj[iobjs].y, sizeof(int));
	read(fd, &mapf->sectors[i].obj[iobjs].type, sizeof(short));
	mapf->sectors[i].obj[iobjs].picked = 0;
	mapf->sectors[i].obj[iobjs].sec = i;
	return (1);
}

int						open_error(char **mapfile)
{
	ft_putendl("We could not open the file");
	free(*mapfile);
	return (0);
}
