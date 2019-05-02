/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_free.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 15:55:19 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 13:52:21 by flombard    ###    #+. /#+    ###.fr     */
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
** Frees all the hud ressources (textures, music, sound)
*/

int			free_hud(t_hud *hud)
{
	int		i;

	i = -1;
	while (++i < 7)
		if (hud->gun[i])
			SDL_FreeSurface(hud->gun[i]);
	if (hud->ammo)
		SDL_FreeSurface(hud->ammo);
	if (hud->life)
		SDL_FreeSurface(hud->life);
	if (hud->key)
		SDL_FreeSurface(hud->key);
	if (hud->armor)
		SDL_FreeSurface(hud->armor);
	free_audio(hud);
	if (hud->arial)
		TTF_CloseFont(hud->arial);
	if (hud->nbammo)
		SDL_FreeSurface(hud->nbammo);
	if (hud->nblife)
		SDL_FreeSurface(hud->nblife);
	TTF_Quit();
	return (0);
}
