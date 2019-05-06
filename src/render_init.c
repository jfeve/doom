/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_init.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 20:13:49 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 20:32:24 by jfeve       ###    #+. /#+    ###.fr     */
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
			if (j !=  sec->nbvert - 1)
				sec->vert[j].texx = vector_measure(sec->vert[j].x, sec->vert[j].y,
						sec->vert[j + 1].x, sec->vert[j + 1].y) / TEXT_S;
			else
				sec->vert[j].texx = vector_measure(sec->vert[j].x, sec->vert[j].y,
						sec->vert[0].x, sec->vert[0].y) / TEXT_S;
			j++;
		}
		i++;
	}
}

void		fill_tab_text(t_mapf *mapf)
{
	SDL_Surface *tmp[4];

	tmp[0] = SDL_LoadBMP("data/textures/wall.bmp");
	tmp[1] = SDL_LoadBMP("data/textures/wall2.bmp");
	tmp[2] = SDL_LoadBMP("data/textures/wall3.bmp");
	tmp[3] = SDL_LoadBMP("data/textures/wall4.bmp");
	mapf->wall[0] = SDL_ConvertSurfaceFormat(tmp[0], SDL_PIXELFORMAT_RGBA8888, 0);
	mapf->wall[1] = SDL_ConvertSurfaceFormat(tmp[1], SDL_PIXELFORMAT_RGBA8888, 0);
	mapf->wall[2] = SDL_ConvertSurfaceFormat(tmp[2], SDL_PIXELFORMAT_RGBA8888, 0);
	mapf->wall[3] = SDL_ConvertSurfaceFormat(tmp[3], SDL_PIXELFORMAT_RGBA8888, 0);
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
	mapf->player.state = nmoving;
	mapf->player.ammo = 5;
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
	{
		free_sdl(&mapf->sdl, 6);
		return (0);
	}
	fill_tex_vert(mapf);
	fill_tab_text(mapf);
	set_lum(mapf);
	fill_settings(mapf);
	return (1);
}

