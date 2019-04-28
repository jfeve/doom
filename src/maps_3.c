/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps_3.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 13:34:28 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 19:31:41 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				mcheck_pos(t_edit *edit)
{
	if (edit->player != NULL)
	{
		if (edit->pl_angle == -1)
			return (0);
		if (edit->finish == NULL)
			return (0);
		return (1);
	}
	else
		return (0);
}

int				mcheck_d(t_lis *temp)
{
	if (temp->x >= 0 && temp->x >= 0 && temp->text != -1)
		return (1);
	else
		return (0);
}

int				mcheck_sec(t_sec *tmp)
{
	if (tmp->floor != -1 && tmp->ceil != -1)
		return (1);
	else
		return (0);
}

int				err_map(char *msg, t_lis *temp)
{
	if (ft_strlen(msg))
	{
		if (temp != NULL)
			free(&temp);
		ft_putendl(msg);
		return (0);
	}
	else
	{
		if (temp != NULL)
			free(temp);
		return (0);
	}
}
