/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 21:32:10 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 00:56:10 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			print_lis(t_lis **vert)
{
	t_lis		*tmp;

	tmp = *vert;
	printf("\n----------LIS----------\n");
	while (tmp != NULL)
	{
		printf("x = %d\ty = %d\n", tmp->x, tmp->y);
		tmp = tmp->next;
	}
	printf("\n--------LIS END--------\n");
}

void			print_sec(t_sec *sec)
{
	t_sec		*tmp;

	tmp = sec;
	printf("\n||||||||SEC||||||||\n");
	while (tmp != NULL)
	{
		printf("vert = %p\n", tmp->vert);
		tmp = tmp->next;
	}
	printf("\n||||||SEC END||||||\n");
}
