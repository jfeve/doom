/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps_3.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 13:34:28 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 18:22:11 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				mcheck_pos(t_edit *edit)
{
	if (edit->player != NULL)
	{
		if (edit->finish != NULL)
			return (1);
		else
			return (0);
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
