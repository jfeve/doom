/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:37:33 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 13:39:41 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	free_hud(t_hud *hud)
{
	int		i;

	i = -1;
	while (++i < 6)
		SDL_FreeSurface(hud->gun[i]);
	if (hud->ammo)
		SDL_FreeSurface(hud->ammo);
}

static int	init_texture(t_hud *hud, Uint32 format)
{
	if (!(hud->tmp = SDL_LoadBMP("data/textures/idle.bmp")))
		return (0);
	if (!(hud->gun[0] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
	{
		SDL_FreeSurface(hud->tmp);
		return (0);
	}
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/shoot1.bmp")))
		return (0);
	if (!(hud->gun[1] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
	{
		SDL_FreeSurface(hud->tmp);
		return (0);
	}
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/shoot2.bmp")))
		return (0);
	if (!(hud->gun[2] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
	{
		SDL_FreeSurface(hud->tmp);
		return (0);
	}
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/recoil1.bmp")))
		return (0);
	if (!(hud->gun[3] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
	{
		SDL_FreeSurface(hud->tmp);
		return (0);
	}
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/recoil2.bmp")))
		return (0);
	if (!(hud->gun[4] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
	{
		SDL_FreeSurface(hud->tmp);
		return (0);
	}
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/recoil3.bmp")))
		return (0);
	if (!(hud->gun[5] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
	{
		SDL_FreeSurface(hud->tmp);
		return (0);
	}
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/ammo.bmp")))
		return (0);
	if (!(hud->ammo = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
	{
		SDL_FreeSurface(hud->tmp);
		return (0);
	}
	SDL_FreeSurface(hud->tmp);
	return (1);
}

static void	draw_cross(t_sdl *sdl)
{
		bresen((t_lis){.x = WIN_W / 2 - 25, .y = WIN_H / 2, .col = 0x000000ff},
		(t_lis){.x = WIN_W / 2 - 10, .y = WIN_H / 2, .col = 0x000000ff}, sdl);
		bresen((t_lis){.x = WIN_W / 2 + 25, .y = WIN_H / 2, .col = 0x000000ff},
		(t_lis){.x = WIN_W / 2 + 10, .y = WIN_H / 2, .col = 0x000000ff}, sdl);
		bresen((t_lis){.x = WIN_W / 2, .y = WIN_H / 2 + 25, .col = 0x000000ff},
		(t_lis){.x = WIN_W / 2, .y = WIN_H / 2 + 10, .col = 0x000000ff}, sdl);
		bresen((t_lis){.x = WIN_W / 2, .y = WIN_H / 2 - 25, .col = 0x000000ff},
		(t_lis){.x = WIN_W / 2, .y = WIN_H / 2 - 10, .col = 0x000000ff}, sdl);
}

static void	draw_hand(t_sdl *sdl, SDL_Surface *s[6], int id)
{
	int		i;
	Uint32	*p;

	SDL_LockSurface(s[id]);
	p = s[id]->pixels;
	i = 0;
	int x, y = WIN_H - s[id]->h;
	while (y < WIN_H)
	{
		x = 2 * WIN_W / 3;
		while (x < 2 * WIN_W / 3 + s[id]->w)
		{
			if (p[i] & 0x000000ff)
				sdl->pix[y * WIN_W + x] = p[i];
			x++;
			i++;
		}
		y++;
	}
	s[id]->pixels = p;
	SDL_UnlockSurface(s[id]);
}


static void	render_check_event(t_input *in, t_hud *hud)
{
	if (in->mouse[SDL_BUTTON_LEFT])
		hud->anim = SDL_TRUE;
}

void		render(void)
{
	t_sdl		sdl;
	t_input		in;
	t_hud		hud;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&sdl, sizeof(t_sdl));
	if (sdl_init(&sdl) == 0)
		return (ft_putendl("Init SDL Error"));
	if (!init_texture(&hud, sdl.form->format))
	{
		free_sdl(&sdl, 6);
		free_hud(&hud);
		return ;
	}
	hud.anim = SDL_FALSE;
	while (!in.quit)
	{
		clear_tab(&sdl);
		update_event(&in);
		render_check_event(&in, &hud);
		if (hud.anim == SDL_FALSE)
			hud.id = 0;
		else
			hud.id++;
		if (hud.id > 5)
		{
			hud.anim = SDL_FALSE;
			hud.id = 0;
		}
		draw_hand(&sdl, hud.gun, hud.id);
		draw_cross(&sdl);
		if (display_frame(sdl.ren, sdl.pix) == 0)
		{
			free_sdl(&sdl, 6);
			free_hud(&hud);
			return ;
		}
		SDL_Delay(1000 / 60);
	}
	free_sdl(&sdl, 6);
	free_hud(&hud);
}
