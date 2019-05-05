/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps_sect.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 17:07:42 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 17:29:07 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	save_d(int fd, t_lis **verts)
{
	t_lis	*lst;

	lst = *verts;
	while (lst != NULL)
	{
		write(fd, &lst->x, sizeof(int));
		write(fd, &lst->y, sizeof(int));
		write(fd, &lst->text, sizeof(short));
		write(fd, &lst->neigh, sizeof(int));
		lst = lst->next;
	}
}

static void	save_objs(int fd, t_lis **alst)
{
	t_lis	*lst;

	lst = *alst;
	while (lst != NULL)
	{
		write(fd, &lst->x, sizeof(int));
		write(fd, &lst->y, sizeof(int));
		write(fd, &lst->text, sizeof(short));
		lst = lst->next;
	}
}

void					putinfo_sec(int fd, t_sec *sect)
{
	save_d(fd, &sect->vert);
	if (sect->obj != NULL && sect->objscount != 0)
		save_objs(fd, &sect->obj);
	if (sect->enem != NULL && sect->enemcount != 0)
		save_objs(fd, &sect->enem);
}
