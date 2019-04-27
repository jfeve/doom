/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:37:33 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 17:26:15 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Frees all the hud textures.
*/

static void	free_hud(t_hud *hud)
{
	int		i;

	i = -1;
	while (++i < 6)
		if (hud->gun[i])
			SDL_FreeSurface(hud->gun[i]);
	if (hud->ammo)
		SDL_FreeSurface(hud->ammo);
}

/*
** Initialize all the textures needed in the hud.
** tmp is here to change the format of the textures, to match the screen's.
*/

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
	if (!(hud->tmp = SDL_LoadBMP("data/textures/life.bmp")))
		return (0);
	if (!(hud->life = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
	{
		SDL_FreeSurface(hud->tmp);
		return (0);
	}
	SDL_FreeSurface(hud->tmp);
	return (1);
}

/*
** Draws the aiming cross in the middle of the screen
*/

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

/*
** Deals with the hud related events (for now)
*/

static void	render_check_event(t_input *in, t_hud *hud, Mix_Chunk *gunshot)
{
	if (in->mouse[SDL_BUTTON_LEFT])
	{
		hud->anim = SDL_TRUE;
		Mix_PlayChannel(1, gunshot, 0);
	}
}

/*
** Draws the sprite contained in s starting at the (x, y) coordinates.
*/

static void	draw_sprite(t_sdl *sdl, SDL_Surface *s, int x, int y)
{
	int		i;
	int		x_index;
	int		y_index;
	Uint32	*p;

	SDL_LockSurface(s);
	p = s->pixels;
	i = 0;
	y_index = y;
	while (y_index < y + s->h)
	{
		x_index = x;
		while (x_index < x + s->w)
		{
			if (p[i] & 0x000000ff)
				sdl->pix[y_index * WIN_W + x_index] = p[i];
			x_index++;
			i++;
		}
		y_index++;
	}
	s->pixels = p;
	SDL_UnlockSurface(s);
}

void		render(void)
{
	t_sdl		sdl;
	t_input		in;
	t_hud		hud;
	Mix_Music	*music;
	Mix_Chunk	*gunshot;

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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		free_sdl(&sdl, 6);
		free_hud(&hud);
		return ;
	}
	if (!(music = Mix_LoadMUS("data/sounds/petit_poney.mp3")))
	{
		free_sdl(&sdl, 6);
		free_hud(&hud);
		Mix_CloseAudio();
		return ;
	}
	if (!(gunshot = Mix_LoadWAV("data/sounds/gun.wav")))
	{
		dprintf(1, "%s\n", Mix_GetError()); 
		free_sdl(&sdl, 6);
		free_hud(&hud);
		Mix_FreeMusic(music);
		Mix_CloseAudio();
		return ;
	}
	Mix_PlayMusic(music, -1);
	while (!in.quit)
	{
		clear_tab(&sdl);
		update_event(&in);
		render_check_event(&in, &hud, gunshot);
		if (hud.anim == SDL_FALSE)
			hud.id = 0;
		else
			hud.id++;
		if (hud.id > 5)
		{
			hud.anim = SDL_FALSE;
			hud.id = 0;
		}
		draw_sprite(&sdl, hud.gun[hud.id], 2 * WIN_W / 3, WIN_H - hud.gun[hud.id]->h);
		draw_sprite(&sdl, hud.ammo, 0, WIN_H - hud.ammo->h);
		draw_sprite(&sdl, hud.life, 0, WIN_H - hud.ammo->h - hud.life->h - 25);
		draw_cross(&sdl);
		if (display_frame(sdl.ren, sdl.pix) == 0)
		{
			free_sdl(&sdl, 6);
			free_hud(&hud);
			Mix_FreeMusic(music);
			Mix_FreeChunk(gunshot);
			Mix_CloseAudio();
			return ;
		}
		SDL_Delay(1000 / 60);
	}
	free_sdl(&sdl, 6);
	free_hud(&hud);
	Mix_FreeMusic(music);
	Mix_FreeChunk(gunshot);
	Mix_CloseAudio();
}
