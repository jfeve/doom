/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 21:32:10 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 15:59:25 by jfeve       ###    #+. /#+    ###.fr     */
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
	dprintf(1, "\n||||||||SEC||||||||\n");
	while (tmp != NULL)
	{
		dprintf(1, "vert = %p\n", tmp->vert);
		tmp = tmp->next;
	}
	dprintf(1, "\n||||||SEC END||||||\n");
}
