/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_init.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:37:33 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 21:06:32 by flombard    ###    #+. /#+    ###.fr     */
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

static int			init_texture(t_hud *hud, Uint32 format)
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
	if (!(hud->gun[6] = init_image("data/textures/noammo.bmp", format)))
		return (0);
	if (!(hud->ammoicon = init_image("data/textures/ammo.bmp", format)))
		return (0);
	if (!(hud->lifeicon = init_image("data/textures/life.bmp", format)))
		return (0);
	if (!(hud->items[0] = init_image("data/textures/key.bmp", format)))
		return (0);
	if (!(hud->items[1] = init_image("data/textures/armor.bmp", format)))
		return (0);
	if (!(hud->items[2] = init_image("data/textures/medkit.bmp", format)))
		return (0);
	if (!(hud->items[3] = init_image("data/textures/ammopack.bmp", format)))
		return (0);
	if (!(hud->items[4] = init_image("data/textures/key_back.bmp", format)))
		return (0);
	if (!(hud->items[5] = init_image("data/textures/armor_back.bmp", format)))
		return (0);
	if (!(hud->items[6] = init_image("data/textures/medkit_back.bmp", format)))
		return (0);
	if (!(hud->items[7] = init_image("data/textures/ammopack_back.bmp", format)))
		return (0);
	if (!(hud->items[8] = init_image("data/textures/flag.bmp", format)))
		return (0);
	if (!(hud->enemy[0] = init_image("data/textures/enemy.bmp", format)))
		return (0);
	if (!(hud->enemy[1] = init_image("data/textures/enemy2.bmp", format)))
		return (0);
	return (1);
}

/*
** Init the font and the default ammo and life numbers
*/

SDL_Surface			*init_text(TTF_Font *font, char *str, Uint32 format, SDL_Color color)
{
	SDL_Surface	*tmp;
	SDL_Surface	*ret;

	if (!(tmp = TTF_RenderText_Solid(font, str, color)))
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
** Initialize the fonts and texts
*/

static int			init_ttf(t_hud *hud, t_player player, Uint32 format)
{
	if(TTF_Init() == -1)
		return (0);
	if (!(hud->arial = TTF_OpenFont("/Library/Fonts/Arial.ttf", 25)))
		return (0);
	if (!(hud->nbammo = init_text(hud->arial, ft_itoa(player.ammo), format, (SDL_Color){0, 0, 0, 255})))
		return (0);
	if (!(hud->nblife = init_text(hud->arial, ft_itoa(player.life), format, (SDL_Color){0, 0, 0, 255})))
		return (0);
	if (!(hud->begin = init_text(hud->arial, "Start !", format, (SDL_Color){255, 255, 255, 255})))
		return (0);
	return (1);
}

/*
** Initialize the textures and sounds of the hud
*/

int					init_hud(t_hud *hud, Uint32 format, t_player player)
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
	if (!(hud->empty = Mix_LoadWAV("data/sounds/empty.wav")))
		return (free_hud(hud));
	init_ttf(hud, player, format);
	hud->anim = SDL_FALSE;
	hud->has_armor = 0;
	hud->has_key = 0;
	hud->timer = 150;
	return (1);
}
