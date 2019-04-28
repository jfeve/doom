/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_begin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
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

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&mapf, sizeof(t_mapf));
	if (!read_map(&mapf, str))
		return ;
	sdl_init(&mapf.sdl);
	SDL_WarpMouseInWindow(mapf.sdl.win, WIN_W / 2, WIN_H / 2);
	if ((SDL_SetRelativeMouseMode(SDL_ENABLE)) != 0)
		return ;
	mapf.player.velo.x = 0;
	mapf.player.velo.y = 0;
	mapf.player.velo.z = 0;
	mapf.player.yaw = 0;
	mapf.player.coll = 0;
	mapf.player.eye = EYE;
	mapf.player.add_z = 0;
	mapf.player.jump_sec = 0;
	mapf.player.state = nmoving;
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
		render_check_event(&mapf, &in);
		fill_pix(&mapf);
		if (display_frame(mapf.sdl.ren, mapf.sdl.pix) == 0)
			return ;
		SDL_Delay(1000 / 60);
	}
}
