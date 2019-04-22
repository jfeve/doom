/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   white_frame.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 23:29:58 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 23:37:45 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			fill_wf(t_edit *edit)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < WF_H)
	{
		j = 0;
		while (j < WF_W)
		{
			if (j < 10 || j > WF_W - 10)
				edit->sdl.white_frame[i * WF_W + j] = PURPLE;
			else
				edit->sdl.white_frame[i * WF_W + j] = WHITE;
			j++;
		}
		i++;
	}
}
/*
 *
 *void			wf_mode(t_input *in, t_edit *edit)
 *{
 *    int			i;
 *    int			j;
 *
 *    i = 500;
 *    while (i < 500 + WF_W)
 *    {
 *
 *    }
 *}
 */
