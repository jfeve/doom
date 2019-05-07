/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_ia.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 19:03:46 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 23:01:23 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int		enemy_ia(t_mapf *mapf, t_hud *hud)
{
	short	i;
	short	j;
	float	res;
	int		taken_dmg;

	taken_dmg = 0;
	if ((i = mapf->nbrend_s) > MAX_SECT)
		i = MAX_SECT;
	while (--i >= 0)
	{
		j = -1;
		t_sector	now = mapf->sectors[mapf->rend_s[i].id];
		while (++j < now.nbenem && j < MAX_SPRITE)
		{
			if ((res = vector_measure(now.enem[j].x,
			now.enem[j].y, mapf->player.where.x,
			mapf->player.where.y)) > 1.5f && res < 15
			&& now.enem[j].life != 0)
			{
					now.enem[j].x += (0.05f / res) * (mapf->player.where.x - now.enem[j].x);
					now.enem[j].y += (0.05f / res) * (mapf->player.where.y - now.enem[j].y);
			}
			else if (vector_measure(now.enem[j].x, 
			now.enem[j].y, mapf->player.where.x,
			mapf->player.where.y) <= 2.0f && now.enem[j].life != 0)
			{
				if (mapf->player.life == 0)
				{
					if (hud->timer == 0)
					{
						hud->timer = -50;
						if (!(hud->text = init_text(hud->arial, "Game Over !", mapf->sdl.form->format, (SDL_Color){255, 255, 255, 255})))
						{
							free_hud(hud);
							return (0);
						}
					}
				}
				else if (mapf->player.life != 0)
					taken_dmg++;
			}
		}
	}
	if (taken_dmg > 0)
	{
		if (hud->has_armor == 1 && taken_dmg > 1)
			taken_dmg = 2 * taken_dmg / 3;
		mapf->player.life -= taken_dmg;
		if (mapf->player.life < 0)
			mapf->player.life = 0;
		SDL_FreeSurface(hud->nblife);
		if (!(hud->nblife = init_text(hud->arial, ft_itoa(mapf->player.life), mapf->sdl.form->format, (SDL_Color){0, 0, 0, 255})))
		{
			free_hud(hud);
			return (0);
		}
	}
	return (1);
}

int		check_finish(t_mapf *mapf, int hud_has_key)
{
	if (mapf->player.sect == mapf->finish_sec
	&& vector_measure(mapf->player.where.x, mapf->player.where.y,
	mapf->finish_x, mapf->finish_y) < 1.0f)
		if (mapf->has_key == 0 || (mapf->has_key == 1 && hud_has_key == 1))
			return (1);
	return (0);
}

void	check_key(t_mapf *mapf)
{
	short	i;
	short	j;

	i = -1;
	mapf->has_key = 0;
	while (++i < mapf->nbsect)
	{
		j = -1;
		while (++j < mapf->sectors[i].nbobjs)
			if (mapf->sectors[i].obj[j].type == 1)
				mapf->has_key = 1;
	}
}
