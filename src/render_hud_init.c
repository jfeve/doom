/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_init.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:37:33 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 16:48:34 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static SDL_Surface	*init_image(char *path, Uint32 format)
{
	SDL_Surface	*tmp;
	SDL_Surface	*ret;

	if (!(tmp = SDL_LoadBMP(path)))
		return (NULL);
	if (!(ret = SDL_ConvertSurfaceFormat(tmp, format, 0)))
	{
		SDL_FreeSurface(tmp);
		return (NULL);
	}
	SDL_FreeSurface(tmp);
	return (ret);
}

/*
** Initialize all the textures needed in the hud.
** tmp is here to change the format of the textures, to match the screen's.
*/

static int	init_texture(t_hud *hud, Uint32 format)
{
	if (!(hud->gun[0] = init_image("data/textures/idle.bmp", format)))
		return (0);
	if (!(hud->gun[1] = init_image("data/textures/shoot1.bmp", format)))
		return (0);
	if (!(hud->gun[2] = init_image("data/textures/shoot2.bmp", format)))
		return (0);
	if (!(hud->gun[3] = init_image("data/textures/recoil1.bmp", format)))
		return (0);
	if (!(hud->gun[4] = init_image("data/textures/recoil2.bmp", format)))
		return (0);
	if (!(hud->gun[5] = init_image("data/textures/recoil3.bmp", format)))
		return (0);
	if (!(hud->ammo = init_image("data/textures/ammo.bmp", format)))
		return (0);
	if (!(hud->life = init_image("data/textures/life.bmp", format)))
		return (0);
	if (!(hud->smallgun = init_image("data/textures/smallgun.bmp", format)))
		return (0);
	return (1);
}

/*
** Initialize the textures and sounds of the hud
*/

int			init_hud(t_hud *hud, Uint32 format)
{
	if (!init_texture(hud, format))
		return (free_hud(hud));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		return (free_hud(hud));
	if (!(hud->music = Mix_LoadMUS("data/sounds/theme.mp3")))
		return (free_hud(hud));
	Mix_Volume(0, MIX_MAX_VOLUME / 3);
	if (!(hud->gunshot = Mix_LoadWAV("data/sounds/gun.wav")))
		return (free_hud(hud));
	hud->anim = SDL_FALSE;
	return (1);
}
