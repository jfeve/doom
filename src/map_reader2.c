/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_reader2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:08:27 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 12:31:45 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				read_enem_data(int fd, t_mapf *mapf, int ienem, int i)
{
	read(fd, &mapf->sectors[i].enem[ienem].x, sizeof(int));
	read(fd, &mapf->sectors[i].enem[ienem].y, sizeof(int));
	read(fd, &mapf->sectors[i].enem[ienem].type, sizeof(short));
	//read(fd, &mapf->sectors[i].obj[ienem].sec, sizeof(short));
	return (1);
}

int				read_objs_data(int fd, t_mapf *mapf, int iobjs, int i)
{
	read(fd, &mapf->sectors[i].obj[iobjs].x, sizeof(int));
	read(fd, &mapf->sectors[i].obj[iobjs].y, sizeof(int));
	read(fd, &mapf->sectors[i].obj[iobjs].type, sizeof(short));
	//read(fd, &mapf->sectors[i].obj[iobjs].sec, sizeof(short));
	mapf->sectors[i].obj[iobjs].picked = 0;
	return (1);
}

int						open_error(char **mapfile)
{
	ft_putendl("We could not open the file");
	ft_strdel(mapfile);
	return (0);
}
