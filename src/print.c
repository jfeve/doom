/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 21:32:10 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 20:16:31 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			print_lis(t_lis **vert)
{
	t_lis		*tmp;

	tmp = *vert;
	dprintf(1, "\n----------LIS----------\n");
	while (tmp != NULL)
	{
		dprintf(1, "x = %d\ty = %d\n", tmp->x, tmp->y);
		tmp = tmp->next;
	}
	dprintf(1, "\n--------LIS END--------\n");
}

void			print_sec(t_sec *sec)
{
	t_sec		*tmp;

	tmp = sec;
	dprintf(1, "\n-------PRINT SEC-------\n");
	if (tmp == NULL)
		dprintf(1, "No Sector");
	while (tmp != NULL)
	{
		dprintf(1, "\n||||||||SEC||||||||\n");
		dprintf(1, "id = %d\n", tmp->id);
		dprintf(1, "floor = %d\n", tmp->floor);
		dprintf(1, "ceil = %d\n", tmp->ceil);
		dprintf(1, "enem = %p\n", tmp->enem);
		dprintf(1, "obj = %p\n", tmp->obj);
		dprintf(1, "vert = %p", tmp->vert);
		dprintf(1, "\n||||||SEC END||||||\n");
		tmp = tmp->next;
	}
	dprintf(1, "\n-----PRINT SEC END-----\n\n");
}
