/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_init.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 20:13:49 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 22:44:29 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void		fill_tex_vert(t_mapf *mapf)
{
	t_sector	*sec;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < mapf->nbsect)
	{
		j = 0;
		sec = &mapf->sectors[i];
		sec->texy = (sec->ceil - sec->floor) / TEXT_SY;
		while (j < mapf->sectors[i].nbvert)
		{
			if (j != sec->nbvert - 1)
				sec->vert[j].texx = vector_measure(sec->vert[j].x,
				sec->vert[j].y, sec->vert[j + 1].x, sec->vert[j + 1].y)
				/ TEXT_S;
			else
				sec->vert[j].texx = vector_measure(sec->vert[j].x,
				sec->vert[j].y, sec->vert[0].x, sec->vert[0].y) / TEXT_S;
			j++;
		}
		i++;
	}
}

static int	fill_tab_text(t_mapf *mapf)
{
	if (!(mapf->wall[0] = init_image("data/textures/wall.bmp",
	SDL_PIXELFORMAT_RGBA8888)))
		return (0);
	if (!(mapf->wall[1] = init_image("data/textures/wall2.bmp",
	SDL_PIXELFORMAT_RGBA8888)))
		return (0);
	if (!(mapf->wall[2] = init_image("data/textures/wall3.bmp",
	SDL_PIXELFORMAT_RGBA8888)))
		return (0);
	if (!(mapf->wall[3] = init_image("data/textures/wall4.bmp",
	SDL_PIXELFORMAT_RGBA8888)))
		return (0);
	return (1);
}

void		set_lum(t_mapf *mapf)
{
	int		i;

	i = 0;
	while (i < mapf->nbsect)
	{
		if (i == mapf->player.sect)
			mapf->sectors[i].lum = 1;
		else
			mapf->sectors[i].lum = 0;
		i++;
	}
}

void		fill_settings(t_mapf *mapf)
{
	mapf->player.velo.x = 0;
	mapf->player.velo.y = 0;
	mapf->player.velo.z = 0;
	mapf->player.yaw = 0;
	mapf->player.coll = 0;
	mapf->player.eye = EYE;
	mapf->player.add_z = 0.0f;
	mapf->player.jump_sec = 0;
	mapf->player.state = moving;
	mapf->player.ammo = 100;
	mapf->player.life = 100;
	mapf->coeff = 1;
}

int			init_mapf(t_mapf *mapf, char *str)
{
	if (read_map(mapf, str) == 0)
		return (0);
	if (sdl_init(&mapf->sdl, RWIN_W, RWIN_H) == 0)
	{
		ft_putendl("Init SDL Error");
		return (0);
	}
	SDL_WarpMouseInWindow(mapf->sdl.win, RWIN_W / 2, RWIN_H / 2);
	if ((SDL_SetRelativeMouseMode(SDL_ENABLE)) != 0)
		return (0);
	fill_tex_vert(mapf);
	if (!(fill_tab_text(mapf)))
		return (0);
	set_lum(mapf);
	fill_settings(mapf);
	return (1);
}
