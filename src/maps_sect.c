/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps_sect.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 17:07:42 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 13:35:13 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	save_d(int fd, t_lis *verts)
{
	t_lis	*lst;

	lst = verts;
	while (lst != NULL)
	{
		write(fd, &lst->x, sizeof(int));
		write(fd, &lst->y, sizeof(int));
		write(fd, &lst->text, sizeof(short));
		write(fd, &lst->neigh, sizeof(int));
		lst = lst->next;
	}
}

int						save_objs(int fd, t_lis *temp, short id_sect)
{
	while (temp != NULL)
	{
		write(fd, &temp->x, sizeof(int));
		write(fd, &temp->y, sizeof(int));
		write(fd, &temp->text, sizeof(short));(void)id_sect;
		//write(fd, &id_sect, sizeof(short));
		temp = temp->next;
	}
	return (1);
}

int						save_error2(char *error, t_lis *temp)
{
	ft_putendl(error);
	free(temp);
	return (0);
}

void					putinfo_sec(int fd, t_sec *sect)
{
	t_lis	*temp;

	save_d(fd, sect->vert);
	if (sect->obj != NULL && sect->objscount != 0)
	{
		temp = sect->obj;
		save_objs(fd, temp, sect->id);
	}
	if (sect->enem != NULL && sect->enemcount != 0)
	{
		temp = sect->enem;
		save_objs(fd, temp, sect->id);
	}
}
