/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_free.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 15:55:19 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 20:50:04 by flombard    ###    #+. /#+    ###.fr     */
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
	free_audio(hud);
	if (hud->arial)
		TTF_CloseFont(hud->arial);
	if (hud->nbammo)
		SDL_FreeSurface(hud->nbammo);
	if (hud->nblife)
		SDL_FreeSurface(hud->nblife);
	if (hud->begin)
		SDL_FreeSurface(hud->begin);
	TTF_Quit();
	return (0);
}
