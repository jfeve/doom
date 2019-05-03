/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_begin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 17:18:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 18:14:55 by flombard    ###    #+. /#+    ###.fr     */
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

void		get_ps(t_mapf *mapf)
{
	t_sector	*sec;
	int			i;
	float		px;
	float		py;
	float		ps;

	px = mapf->player.where.x;
	py = mapf->player.where.y;
	sec = &mapf->sectors[mapf->player.sect];
	i = 0;
	while (i < sec->nbvert)
	{
		if (i != sec->nbvert - 1)
		{
			ps = f_pointside((t_float){px, py}, (t_float){sec->vert[i].x, sec->vert[i].y},
						(t_float){sec->vert[i + 1].x, sec->vert[i + 1].y});
			dprintf(1, "tps = %f\n", ps);
			if (ps > 0)
				sec->vert[i].ps = 1;
			else if (ps < 0)
				sec->vert[i].ps = -1;
			else
				sec->vert[i].ps = 0;
		}
		else
		{
			ps = f_pointside((t_float){px, py}, (t_float){sec->vert[i].x, sec->vert[i].y},
						(t_float){sec->vert[0].x, sec->vert[0].y});
			dprintf(1, "tps = %f\n", ps);
			if (f_pointside((t_float){px, py}, (t_float){sec->vert[i].x, sec->vert[i].y},
						(t_float){sec->vert[0].x, sec->vert[0].y}) > 0)
				sec->vert[i].ps = 1;
			else if (f_pointside((t_float){px, py}, (t_float){sec->vert[i].x, sec->vert[i].y},
						(t_float){sec->vert[0].x, sec->vert[0].y}) < 0)
				sec->vert[i].ps = -1;
			else
				sec->vert[i].ps = 0;
		}
		i++;
	}
}

void		print_ps(t_mapf *mapf)
{
	t_sector	*sec;
	int			i;

	sec = &mapf->sectors[mapf->player.sect];
	i = 0;
	dprintf(1, "----------------------------------------\n");
	while (i < sec->nbvert)
	{
		dprintf(1, "ps = %d\n", sec->vert[i].ps);
		i++;
	}
}

int		check_ps(t_mapf *mapf)
{
	t_sector *sec;
	int		i;
	float	ps;

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
				if (sec->vert[i].neigh != -1)
				{
					if (mapf->player.where.z - mapf->player.eye + KNEE > mapf->sectors[sec->vert[i].neigh].floor &&
							mapf->player.where.z < mapf->sectors[sec->vert[i].neigh].ceil)
					{
						if (mapf->player.state == flying)
							mapf->player.add_z -= mapf->sectors[sec->vert[i].neigh].floor - mapf->sectors[mapf->player.sect].floor;
						mapf->player.sect = sec->vert[i].neigh;
						if (mapf->player.state != jumping && mapf->player.state != flying && mapf->player.state != crouching)
							mapf->player.state = falling;
						return (0);
					}
				}
				else
				{
					mapf->player.where = (t_xyz){mapf->old.x, mapf->old.y, mapf->old.z};
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
				if (mapf->player.where.z - mapf->player.eye + KNEE > mapf->sectors[sec->vert[i].neigh].floor &&
						mapf->player.where.z < mapf->sectors[sec->vert[i].neigh].ceil)
				{
					if (mapf->player.state == flying)
						mapf->player.add_z -= mapf->sectors[sec->vert[i].neigh].floor - mapf->sectors[mapf->player.sect].floor;
					mapf->player.sect = sec->vert[i].neigh;
					if (mapf->player.state != jumping && mapf->player.state != flying && mapf->player.state != crouching)
						mapf->player.state = falling;
					return (0);
				}
				else
				{
					mapf->player.where = (t_xyz){mapf->old.x, mapf->old.y, mapf->old.z};
				}
			}
		}
		i++;
	}
	return (1);
}

void		render(char *str)
{
	t_mapf	mapf;
	t_input	in;
	t_hud	hud;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&mapf, sizeof(t_mapf));
	ft_bzero(&hud, sizeof(t_hud));
	if (read_map(&mapf, str) == 0)
		return ;
	if (sdl_init(&mapf.sdl) == 0)
		return (ft_putendl("Init SDL Error"));
	SDL_WarpMouseInWindow(mapf.sdl.win, WIN_W / 2, WIN_H / 2);
	if ((SDL_SetRelativeMouseMode(SDL_ENABLE)) != 0)
		return ;
	mapf.player.velo.x = 0;
	mapf.player.velo.y = 0;
	mapf.player.velo.z = 0;
	mapf.player.yaw = 0;
	mapf.player.coll = 0;
	mapf.player.eye = EYE;
	mapf.player.add_z = 0.0f;
	mapf.player.jump_sec = 0;
	mapf.player.state = nmoving;
	mapf.player.ammo = 5;
	mapf.player.life = 100;
	mapf.coeff = 1;
	if (!init_hud(&hud, mapf.sdl.form->format, mapf.player))
		return (ft_putendl("HUD Init Error"));
	//Mix_PlayMusic(hud.music, -1);
	while (!in.quit)
	{
		in.xrel = 0;
		in.yrel = 0;
		ft_bzero(&mapf.rend_s, MAX_SECT * sizeof(int));
		mapf.nbrend_s = 0;
		clear_tab(&mapf.sdl);
		update_event(&in);
		render_check_event(&mapf, &in, &hud);
		check_ps(&mapf);
		if (mapf.player.state == jumping || mapf.player.state == falling)
		{
			mapf.player.where.z = mapf.sectors[mapf.player.jump_sec].floor + EYE + mapf.player.add_z;
			if (mapf.player.where.z < mapf.sectors[mapf.player.sect].floor + EYE)
			{
				mapf.player.where.z = mapf.sectors[mapf.player.sect].floor + EYE;
				mapf.player.state = nmoving;
				mapf.player.add_z = 0;
			}
		}
		else if (mapf.player.state == flying)
		{
			mapf.player.where.z = mapf.sectors[mapf.player.sect].floor + mapf.player.eye + mapf.player.add_z;
			if (mapf.player.where.z > mapf.sectors[mapf.player.sect].ceil)
				mapf.player.add_z -= mapf.player.where.z - mapf.sectors[mapf.player.sect].ceil;
		}
		else
			mapf.player.where.z = mapf.sectors[mapf.player.sect].floor + mapf.player.eye + mapf.player.add_z;
		fill_pix(&mapf);
		draw_items(&mapf, hud.items);
		draw_hud(&mapf.sdl, &hud, mapf.player.ammo);
		if (display_frame(mapf.sdl.ren, mapf.sdl.pix) == 0)
			return ;
		mapf.old = (t_xyz){mapf.player.where.x/* - mapf.player.velo.x*/, mapf.player.where.y/* - mapf.player.velo.y*/, mapf.player.where.z/* - mapf.player.velo.z*/};
		SDL_Delay(1000 / 60);
	}
	free_sdl(&mapf.sdl, 6);
	free_hud(&hud);
}
