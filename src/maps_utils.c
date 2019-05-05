/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 13:34:28 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 13:41:49 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				mcheck_pos(t_edit *edit)
{
	if (edit->player != NULL && edit->finish != NULL && edit->pl_angle != -1)
			return (1);
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

int				unset_map(int id)
{
	ft_putstr("Sector number ");
	ft_putnbr(id);
	ft_putendl(" has unset floor or ceiling heights");
	return (0);
}
