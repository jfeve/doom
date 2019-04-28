/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_init.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:37:33 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 16:20:11 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Initialize all the textures needed in the hud.
** tmp is here to change the format of the textures, to match the screen's.
*/

static int	init_texture(t_hud *hud, Uint32 format)
{
	if (!(hud->tmp = SDL_LoadBMP("data/textures/idle.bmp")))
		return (0);
	if (!(hud->gun[0] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/shoot1.bmp")))
		return (0);
	if (!(hud->gun[1] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/shoot2.bmp")))
		return (0);
	if (!(hud->gun[2] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/recoil1.bmp")))
		return (0);
	if (!(hud->gun[3] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/recoil2.bmp")))
		return (0);
	if (!(hud->gun[4] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/recoil3.bmp")))
		return (0);
	if (!(hud->gun[5] = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/ammo.bmp")))
		return (0);
	if (!(hud->ammo = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/life.bmp")))
		return (0);
	if (!(hud->life = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	if (!(hud->tmp = SDL_LoadBMP("data/textures/smallgun.bmp")))
		return (0);
	if (!(hud->smallgun = SDL_ConvertSurfaceFormat(hud->tmp, format, 0)))
		return (0);
	SDL_FreeSurface(hud->tmp);
	return (1);
}

/*
** Initialize the textures and sounds of the hud
*/

int			init_hud(t_hud *hud, Uint32 format)
{
	if (!init_texture(hud, format))
		return (free_hud(hud));
	hud->anim = SDL_FALSE;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		return (free_hud(hud));
	if (!(hud->music = Mix_LoadMUS("data/sounds/theme.mp3")))
		return (free_hud(hud));
	Mix_Volume(0, MIX_MAX_VOLUME / 3);
	if (!(hud->gunshot = Mix_LoadWAV("data/sounds/gun.wav")))
		return (free_hud(hud));
	return (1);
}
