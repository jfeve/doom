/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_pick_items.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/03 16:35:10 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 22:04:59 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Compute whether or not an item in the player sector is picked
** 1: key, 2: armor, 3:life kit, 4: ammo pack
*/

static int	tests(t_mapf *mapf, t_hud *hud, t_sector now, int i)
{
	char	*tmp;

	if (now.obj[i].type == 1)
		hud->has_key = 1;
	else if (now.obj[i].type == 2)
		hud->has_armor = 1;
	else if (now.obj[i].type == 3)
	{
		if (mapf->player.life <= 60)
			mapf->player.life += 40;
		else
			mapf->player.life = 100;
		SDL_FreeSurface(hud->nblife);
		if (!(tmp = ft_itoa(mapf->player.life)))
			return (0);
		if (!(hud->nblife = init_text(hud->arial, tmp, mapf->sdl.form->format,
		SDL_BLACK)))
		{
			ft_strdel(&tmp);
			return (0);
		}
		ft_strdel(&tmp);
	}
	else if (now.obj[i].type == 4)
	{
		mapf->player.ammo += 10;
		SDL_FreeSurface(hud->nbammo);
		if (!(tmp = ft_itoa(mapf->player.ammo)))
			return (0);
		if (!(hud->nbammo = init_text(hud->arial, tmp, mapf->sdl.form->format,
		SDL_BLACK)))
		{
			ft_strdel(&tmp);
			return (0);
		}
		ft_strdel(&tmp);
	}
	mapf->sectors[mapf->player.sect].obj[i].picked = 1;
	return (1);
}

int			pick_items(t_mapf *mapf, t_hud *hud)
{
	int			i;
	t_sector	now;

	i = -1;
	now = mapf->sectors[mapf->player.sect];
	while (++i < now.nbobjs)
		if (now.obj[i].picked == 0 && vector_measure(mapf->player.where.x,
		mapf->player.where.y, now.obj[i].x, now.obj[i].y) <= 2.0f)
			if (!tests(mapf, hud, now, i))
				return (0);
	return (1);
}

void		check_key(t_mapf *mapf)
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
