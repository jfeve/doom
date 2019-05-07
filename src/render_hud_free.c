/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_free.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 15:55:19 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 19:01:10 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Frees all the audio part (music, sound effect)
*/

static void	free_audio(t_hud *hud)
{
	if (hud->music)
		Mix_FreeMusic(hud->music);
	if (hud->gunshot)
		Mix_FreeChunk(hud->gunshot);
	if (hud->empty)
		Mix_FreeChunk(hud->empty);
	Mix_CloseAudio();
}

/*
** Frees all the textures
*/

static void	free_tex(t_hud *hud)
{
	int		i;

	i = -1;
	while (++i < 7)
		if (hud->gun[i])
			SDL_FreeSurface(hud->gun[i]);
	i = -1;
	while (++i < 9)
		if (hud->items[i])
			SDL_FreeSurface(hud->items[i]);
	if (hud->enemy[0])
		SDL_FreeSurface(hud->enemy[0]);
	if (hud->enemy[1])
		SDL_FreeSurface(hud->enemy[1]);
	if (hud->ammoicon)
		SDL_FreeSurface(hud->ammoicon);
	if (hud->lifeicon)
		SDL_FreeSurface(hud->lifeicon);
}

/*
** Frees all the hud ressources (textures, music, sound)
*/

int			free_hud(t_hud *hud)
{
	free_audio(hud);
	free_tex(hud);
	if (hud->arial)
		TTF_CloseFont(hud->arial);
	if (hud->nbammo)
		SDL_FreeSurface(hud->nbammo);
	if (hud->nblife)
		SDL_FreeSurface(hud->nblife);
	if (hud->text)
		SDL_FreeSurface(hud->text);
	TTF_Quit();
	return (0);
}

/*
** Load a bmp located at path and convert it to the given format
** Placed here because of the norm
*/

SDL_Surface	*init_image(char *path, Uint32 format)
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
