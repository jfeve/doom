/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_ia.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 19:03:46 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 21:38:23 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void	enemy_ia(t_mapf *mapf)
{
	short	i;
	short	j;
	float	res;

	i = -1;
	while (++i < mapf->nbsect)
	{
		j = -1;
		while (++j < mapf->sectors[i].nbenem)
		{
			if ((res = vector_measure(mapf->sectors[i].enem[j].x, 
			mapf->sectors[i].enem[j].y, mapf->player.where.x,
			mapf->player.where.y)) > 1.5f)
			{
				mapf->sectors[i].enem[j].x += (0.1f / res) * (mapf->player.where.x - mapf->sectors[i].enem[j].x);
				mapf->sectors[i].enem[j].y += (0.1f / res) * (mapf->player.where.y - mapf->sectors[i].enem[j].y);
			}
		}
	}
}
