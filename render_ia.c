/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_ia.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 19:03:46 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 19:20:48 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*void	enemy_ia(t_player player, t_enem *enem)
{
	int		i;
	float	res;
	float	deltax;
	float	deltay;

	i = -1;
	while (enem[++i])
		if (vector_measure(enem[i].x, enem[i].y, player.where.x, player.where.y) > 0.5f)
		{
			deltax = enem[i].x - player.where.x;	//get the sign
			deltay = enem[i].y - player.where.y;	//get the sign
			enem[i].x += signx * 0.2f;
			enem[i].y += signy * 0.2f;
		}
}*/