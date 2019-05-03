/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_pick_items.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/03 16:35:10 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 19:44:26 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Compute whether or not an item in the player sector is picked
** 1: key, 2: armor, 3:life kit, 4: ammo pack
*/

void	pick_items(t_mapf *mapf, t_hud *hud)
{
	int			i;
	t_sector	now;
	t_player	player;

	i = -1;
	player = mapf->player;
	now = mapf->sectors[player.sect];
	while (++i < now.nbobjs)
		if (now.obj[i].picked == 0 && vector_measure(player.where.x, player.where.y, now.obj[i].x, now.obj[i].y) <= 2.0f)
		{
			if (now.obj[i].type == 1)
				hud->has_key = 1;
			else if (now.obj[i].type == 2)
				hud->has_armor = 1;
			else if (now.obj[i].type == 3)
			{
				if (player.life <= 60)
					mapf->player.life += 40;
				else
					mapf->player.life = 100;
				SDL_FreeSurface(hud->nblife);
				if (!(hud->nblife = init_text(hud->arial, ft_itoa(mapf->player.life), mapf->sdl.form->format)))
				{
					free_hud(hud);
					return ;
				}
			}
			else if (now.obj[i].type == 4)
			{
				mapf->player.ammo += 10;
				SDL_FreeSurface(hud->nbammo);
				if (!(hud->nbammo = init_text(hud->arial, ft_itoa(mapf->player.ammo), mapf->sdl.form->format)))
				{
					free_hud(hud);
					return ;
				}
			}
			mapf->sectors[player.sect].obj[i].picked = 1;
		}
}
