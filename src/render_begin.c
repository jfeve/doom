/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_begin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 17:18:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 12:12:43 by jfeve       ###    #+. /#+    ###.fr     */
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

void		render(char *str)
{
	t_mapf	mapf;
	t_input	in;
	t_hud	hud;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&mapf, sizeof(t_mapf));
	ft_bzero(&mapf, sizeof(t_hud));
	read_map(&mapf, str);
	if (sdl_init(&mapf.sdl) == 0)
		return (ft_putendl("Init SDL Error"));
	SDL_WarpMouseInWindow(mapf.sdl.win, WIN_W / 2, WIN_H / 2);
	if ((SDL_SetRelativeMouseMode(SDL_ENABLE)) != 0)
		return ;
	if (!init_hud(&hud, mapf.sdl.form->format))
		return (ft_putendl("Init SDL_Mixer Error"));
	mapf.player.velo.x = 0;
	mapf.player.velo.y = 0;
	mapf.player.velo.z = 0;
	mapf.player.yaw = 0;
	mapf.player.coll = 0;
	mapf.player.eye = EYE;
	mapf.player.add_z = 0;
	mapf.player.jump_sec = 0;
	mapf.player.state = nmoving;
	Mix_PlayMusic(hud.music, -1);
	while (!in.quit)
	{
		in.xrel = 0;
		in.yrel = 0;
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
		clear_tab(&mapf.sdl);
		update_event(&in);
		render_check_event(&mapf, &in, &hud);
		fill_pix(&mapf);
		draw_hud(&mapf.sdl, &hud);
		if (display_frame(mapf.sdl.ren, mapf.sdl.pix) == 0)
			return ;
		SDL_Delay(1000 / 60);
	}
	free_sdl(&mapf.sdl, 6);
	free_hud(&hud);
}
