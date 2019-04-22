/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps_bis.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 17:07:42 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 17:32:17 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int						open_error(char **mapfile)
{
	ft_putendl("We could not open the file");
	free(mapfile);
	return (0);
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
	if ((temp = tmp->enem))
	{
		save_d(fd, temp);
		if ((temp = tmp->obj))
			save_d(fd, temp);
		else
			save_error2("Error while saving the Objects", temp);
	}
	else
		save_error2("Error while saving the Enemies", temp);
}
