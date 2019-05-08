/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps_bis.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 17:07:42 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 21:20:18 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int		save_d(int fd, t_lis *temp)
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

int		save_objs(int fd, t_lis *temp)
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

void	putinfo_sec(int fd, t_lis *temp, t_sec *tmp)
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

int		tar(void)
{
	char	*args[5];
	int		tmp;
	pid_t	child;

	args[0] = "/usr/bin/tar";
	args[1] = "-cf";
	args[2] = "map.tar";
	args[3] = "data/";
	args[4] = NULL;
	if ((child = fork()) == -1)
		return (0);
	if (child == 0)
	{
		execve("/usr/bin/tar", args, NULL);
		exit(EXIT_SUCCESS);
	}
	else
		while (wait(&tmp) != child)
			;
	return (1);
}
