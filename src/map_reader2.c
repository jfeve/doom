/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_reader2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:08:27 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 18:14:53 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				read_enem_data(int fd, t_mapf *mapf, int ienem)
{
	read(fd, &mapf->enemies[ienem].x, sizeof(int));
	read(fd, &mapf->enemies[ienem].y, sizeof(int));
	read(fd, &mapf->enemies[ienem].type, sizeof(short));
	return (1);
}

int				read_objs_data(int fd, t_mapf *mapf, int iobjs)
{
	read(fd, &mapf->objects[iobjs].x, sizeof(int));
	read(fd, &mapf->objects[iobjs].y, sizeof(int));
	read(fd, &mapf->objects[iobjs].type, sizeof(short));
	return (1);
}

int						open_error(char **mapfile)
{
	ft_putendl("We could not open the file");
	free(mapfile);
	return (0);
}
