/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps_bis.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 17:07:42 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 18:14:47 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int						save_d(int fd, t_lis *temp)
{
	while (temp != NULL)
	{
		write(fd, &temp->x, sizeof(int));
		write(fd, &temp->y, sizeof(int));
		write(fd, &temp->text, sizeof(short));
		write(fd, &temp->neigh, sizeof(int));
		temp = temp->next;
	}
	return (1);
}

int						save_objs(int fd, t_lis *temp)
{
	while (temp != NULL)
	{
		write(fd, &temp->x, sizeof(int));
		write(fd, &temp->y, sizeof(int));
		write(fd, &temp->text, sizeof(short));
		temp = temp->next;
	}
	return (1);
}

int						save_error(char *mapfile)
{
	ft_putendl("There has been an error while saving the file");
	free(&mapfile);
	return (0);
}

int						save_error2(char *error, t_lis *temp)
{
	ft_putendl(error);
	free(temp);
	return (0);
}

void					putinfo_sec(int fd, t_lis *temp, t_sec *tmp)
{
	save_d(fd, temp);
	if (tmp->obj != NULL && tmp->objscount != 0)
	{
		temp = tmp->obj;
		save_objs(fd, temp);
	}
	if (tmp->enem != NULL && tmp->enemcount != 0)
	{
		temp = tmp->enem;
		save_objs(fd, temp);
	}
}
