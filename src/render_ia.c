/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_ia.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 19:03:46 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 19:01:03 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static int	compute_takendmg(t_mapf *mapf, t_hud *hud, int taken_dmg)
{
	if (taken_dmg > 0)
	{
		if (hud->has_armor == 1 && taken_dmg > 1)
			taken_dmg = 2 * taken_dmg / 3;
		mapf->player.life -= taken_dmg;
		if (mapf->player.life < 0)
			mapf->player.life = 0;
		SDL_FreeSurface(hud->nblife);
		if (!(hud->nblife = init_text(hud->arial, ft_itoa(mapf->player.life),
		mapf->sdl.form->format, SDL_BLACK)))
			return (0);
	}
	return (1);
}

static int	player_dmg(t_mapf *mapf, t_hud *hud, int *taken_dmg)
{
	if (mapf->player.life == 0)
	{
		if (hud->timer == 0)
		{
			hud->timer = -50;
			if (!(hud->text = init_text(hud->arial, "Game Over !",
			mapf->sdl.form->format, SDL_WHITE)))
				return (0);
		}
	}
	else if (mapf->player.life != 0)
		(*taken_dmg)++;
	return (1);
}

static int	norm2(t_mapf *mapf, t_hud *hud, t_enemies *enem, int *taken_dmg)
{
	float		res;

	if ((res = vector_measure(enem->x, enem->y, mapf->player.where.x,
	mapf->player.where.y)) > 1.5f && res < 15 && enem->life != 0)
	{
		enem->x += (0.05f / res) * (mapf->player.where.x - enem->x);
		enem->y += (0.05f / res) * (mapf->player.where.y - enem->y);
	}
	else if (vector_measure(enem->x, enem->y, mapf->player.where.x,
	mapf->player.where.y) <= 2.0f && enem->life != 0 && enem->life
	== mapf->player.sect)
		if (!player_dmg(mapf, hud, taken_dmg))
			return (0);
	return (1);
}

int			enemy_ia(t_mapf *mapf, t_hud *hud)
{
	short		i;
	short		j;
	int			taken_dmg;
	t_sector	now;

	taken_dmg = 0;
	if ((i = mapf->nbrend_s) > MAX_SECT)
		i = MAX_SECT;
	while (--i >= 0)
	{
		j = -1;
		now = mapf->sectors[mapf->rend_s[i].id];
		while (++j < now.nbenem && j < MAX_SPRITE)
			if (!(norm2(mapf, hud, &now.enem[j], &taken_dmg)))
				return (0);
	}
	if (!compute_takendmg(mapf, hud, taken_dmg))
		return (0);
	return (1);
}

int			check_finish(t_mapf *mapf, int hud_has_key)
{
	if (mapf->player.sect == mapf->finish_sec
	&& vector_measure(mapf->player.where.x, mapf->player.where.y,
	mapf->finish_x, mapf->finish_y) < 1.0f)
		if (mapf->has_key == 0 || (mapf->has_key == 1 && hud_has_key == 1))
			return (1);
	return (0);
}
