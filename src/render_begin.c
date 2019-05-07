/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_begin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 17:18:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 13:17:20 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

float		vector_measure(float x1, float y1, float x2, float y2)
{
	float dx;
	float dy;
	float res;

	dx = x2 - x1;
	dy = y2 - y1;
	res = sqrtf(dx * dx + dy * dy);
	return (res);
}

int		check_ps(t_mapf *mapf)
{
	t_sector *sec;
	int		i;
	float	ps;
	int		cpt = 0;

	i = 0;
	sec = &mapf->sectors[mapf->player.sect];
	while (i < sec->nbvert)
	{
		if (i != sec->nbvert - 1)
		{
			ps = f_pointside((t_float){mapf->player.where.x, mapf->player.where.y},
					(t_float){sec->vert[i].x, sec->vert[i].y},
					(t_float){sec->vert[i + 1].x, sec->vert[i + 1].y});
			if (ps < 0)
			{
				cpt++;
				if (sec->vert[i].neigh != -1)
				{
					if (mapf->player.where.z - mapf->player.eye + KNEE > mapf->sectors[sec->vert[i].neigh].floor &&
							mapf->player.where.z < mapf->sectors[sec->vert[i].neigh].ceil)
					{
						if (mapf->player.state != jumping && mapf->player.state != flying && mapf->player.state != crouching)
							mapf->player.state = falling;
						mapf->sectors[mapf->player.sect].lum = 0;
						mapf->player.sect = sec->vert[i].neigh;
						mapf->sectors[mapf->player.sect].lum = 1;
						if (mapf->player.state != jumping && mapf->player.state != flying)
							mapf->player.state = falling;
						return (0);
					}
				}
			}
		}
		else
		{
			ps = f_pointside((t_float){mapf->player.where.x, mapf->player.where.y},
					(t_float){sec->vert[i].x, sec->vert[i].y},
					(t_float){sec->vert[0].x, sec->vert[0].y});
			if (ps < 0)
			{
				if (sec->vert[i].neigh == -1)
				{
					i++;
					mapf->player.where = (t_xyz){mapf->old.x, mapf->old.y, mapf->old.z};
				}
				else
				{
					if (mapf->player.where.z - mapf->player.eye + KNEE > mapf->sectors[sec->vert[i].neigh].floor &&
							mapf->player.where.z < mapf->sectors[sec->vert[i].neigh].ceil)
					{
						if (mapf->player.state != jumping && mapf->player.state != flying && mapf->player.state != crouching)
							mapf->player.state = falling;
						mapf->sectors[mapf->player.sect].lum = 0;
						mapf->player.sect = sec->vert[i].neigh;
						mapf->sectors[mapf->player.sect].lum = 1;
						if (mapf->player.state != jumping && mapf->player.state != flying)
							mapf->player.state = falling;
						return (0);
					}
				}
			}
		}
		i++;
	}
	if (cpt)
		mapf->player.where = (t_xyz){mapf->old.x, mapf->old.y, mapf->old.z};
	return (1);
}

void		check_state(t_mapf *mapf)
{
	if (mapf->player.state == jumping || mapf->player.state == falling)
	{
		mapf->player.where.z = mapf->sectors[mapf->player.sect].floor + EYE + mapf->player.add_z;
		if (mapf->player.where.z < mapf->sectors[mapf->player.sect].floor + EYE)
		{
			mapf->player.where.z = mapf->sectors[mapf->player.sect].floor + EYE;
			mapf->player.state = moving;
			mapf->player.add_z = 0;
		}
	}
	else if (mapf->player.state == flying)
	{
		mapf->player.where.z = mapf->sectors[mapf->player.sect].floor + mapf->player.eye + mapf->player.add_z;
		if (mapf->player.where.z > mapf->sectors[mapf->player.sect].ceil)
			mapf->player.add_z -= mapf->player.where.z - mapf->sectors[mapf->player.sect].ceil;
	}
	else
		mapf->player.where.z = mapf->sectors[mapf->player.sect].floor + mapf->player.eye + mapf->player.add_z;
}

void		render(char *str)
{
	t_mapf	mapf;
	t_input	in;
	t_hud	hud;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&mapf, sizeof(t_mapf));
	ft_bzero(&hud, sizeof(t_hud));
	if (init_mapf(&mapf, str) == 0)
	{
		free_sdl(&mapf.sdl, 6);
		return (ft_putendl("Init Mapf Error"));
	}
	if (!init_hud(&hud, mapf.sdl.form->format, mapf.player))
		return (ft_putendl("Init SDL_Mixer Error"));
//	Mix_PlayMusic(hud.music, -1);
	while (!in.quit)
	{
		in.xrel = 0;
		in.yrel = 0;
		update_event(&in);
		render_check_event(&mapf, &in, &hud);
		check_ps(&mapf);
		ft_bzero(&mapf.rend_s, MAX_SECT * sizeof(int));
		mapf.nbrend_s = 0;
		check_state(&mapf);
		clear_tab(&mapf.sdl, RWIN_W, RWIN_H);
		fill_pix(&mapf);
		enemy_ia(&mapf, &hud);
		draw_entities(&mapf, hud.items, hud.enemy, &in);
		draw_hud(&mapf.sdl, &hud, mapf.player.ammo);
		if (display_frame(mapf.sdl.ren, mapf.sdl.pix, RWIN_W, RWIN_H) == 0)
			return ;
		mapf.old = (t_xyz){mapf.player.where.x - mapf.player.velo.x, mapf.player.where.y - mapf.player.velo.y, mapf.player.where.z - mapf.player.velo.z};
//		SDL_Delay(1000 / 60);
	}
	free_sdl(&mapf.sdl, 6);
	free_hud(&hud);
}
