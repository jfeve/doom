/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_begin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 17:18:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 20:50:08 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	check_state(t_mapf *mapf)
{
	if (mapf->player.state == jumping || mapf->player.state == falling)
	{
		mapf->player.where.z = mapf->sectors[mapf->player.sect].floor + EYE
		+ mapf->player.add_z;
		if (mapf->player.where.z < mapf->sectors[mapf->player.sect].floor + EYE)
		{
			mapf->player.where.z = mapf->sectors[mapf->player.sect].floor + EYE;
			mapf->player.state = moving;
			mapf->player.add_z = 0;
		}
	}
	else if (mapf->player.state == flying)
	{
		mapf->player.where.z = mapf->sectors[mapf->player.sect].floor
		+ mapf->player.eye + mapf->player.add_z;
		if (mapf->player.where.z > mapf->sectors[mapf->player.sect].ceil)
			mapf->player.add_z -= mapf->player.where.z
			- mapf->sectors[mapf->player.sect].ceil;
	}
	else
		mapf->player.where.z = mapf->sectors[mapf->player.sect].floor
		+ mapf->player.eye + mapf->player.add_z;
}

void		render(char *str)
{
	t_mapf	mapf;
	t_input	in;
	t_hud	hud;
	int		tmp;

	if (!untar(&tmp))
		return ;
	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&mapf, sizeof(t_mapf));
	ft_bzero(&hud, sizeof(t_hud));
	if (init_mapf(&mapf, str) == 0)
	{
		free_sdl(&mapf.sdl, 6);
		ft_putendl("Init Mapf Error");
		return ;
	}
	if (!init_hud(&hud, mapf.sdl.form->format, mapf.player))
	{
		ft_putendl("Init SDL_Mixer Error");
		return ;
	}
	Mix_PlayMusic(hud.music, -1);
	while (!in.quit)
	{
		in.xrel = 0;
		in.yrel = 0;
		update_event(&in);
		if (!render_check_event(&mapf, &in, &hud))
		{
			free_sdl(&mapf.sdl, 6);
			free_hud(&hud);
			ft_putendl("Internal error");
			return ;
		}
		check_ps(&mapf);
		ft_bzero(&mapf.rend_s, MAX_SECT * sizeof(int));
		mapf.nbrend_s = 0;
		check_state(&mapf);
		if (check_finish(&mapf, hud.has_key))
			break ;
		clear_tab(&mapf.sdl, RWIN_W, RWIN_H);
		fill_pix(&mapf);
		if (!enemy_ia(&mapf, &hud))
		{
			free_sdl(&mapf.sdl, 6);
			free_hud(&hud);
			ft_putendl("Internal error");
			return ;
		}
		draw_entities(&mapf, hud.items, hud.enemy, &in);
		draw_hud(&mapf.sdl, &hud, mapf.player.ammo);
		if (display_frame(mapf.sdl.ren, mapf.sdl.pix, RWIN_W, RWIN_H) == 0)
		{
			free_sdl(&mapf.sdl, 6);
			free_hud(&hud);
			ft_putendl("Internal error");
			return ;
		}
		mapf.old = (t_xyz){mapf.player.where.x - mapf.player.velo.x, mapf.player.where.y - mapf.player.velo.y, mapf.player.where.z - mapf.player.velo.z};
		if (hud.timer == -1)
		{
			free_sdl(&mapf.sdl, 6);
			free_hud(&hud);
			return ;
		}
	}
	free_sdl(&mapf.sdl, 6);
	free_hud(&hud);
}
