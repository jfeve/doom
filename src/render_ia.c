/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_ia.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 19:03:46 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 09:23:41 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void	enemy_ia(t_mapf *mapf, t_hud *hud)
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
			mapf->player.where.y)) > 1.5f && res < 15 &&
					mapf->sectors[i].enem[j].life != 0)
			{
					mapf->sectors[i].enem[j].x += (0.05f / res) * (mapf->player.where.x - mapf->sectors[i].enem[j].x);
					mapf->sectors[i].enem[j].y += (0.05f / res) * (mapf->player.where.y - mapf->sectors[i].enem[j].y);
			}
			else if (vector_measure(mapf->sectors[i].enem[j].x, 
			mapf->sectors[i].enem[j].y, mapf->player.where.x,
			mapf->player.where.y) <= 2.0f && mapf->sectors[i].enem[j].life != 0)
			{
				if (mapf->player.life == 0)
				{
					hud->timer = -1;
					if (!(hud->begin = init_text(hud->arial, "Game Over !", mapf->sdl.form->format, (SDL_Color){255, 255, 255, 255})))
					{
						free_hud(hud);
						return ;
					}
				}
				else if (mapf->player.life != 0)
					mapf->player.life--;
				SDL_FreeSurface(hud->nblife);
				if (!(hud->nblife = init_text(hud->arial, ft_itoa(mapf->player.life), mapf->sdl.form->format, (SDL_Color){0, 0, 0, 255})))
				{
					free_hud(hud);
					return ;
				}
			}
		}
	}
}
