/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_hud_free.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 15:55:19 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 16:53:44 by flombard    ###    #+. /#+    ###.fr     */
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
		SDL_FreeSurface(hud->gun[i]);
	i = -1;
	while (++i < 9)
		SDL_FreeSurface(hud->items[i]);
	SDL_FreeSurface(hud->enemy[0]);
	SDL_FreeSurface(hud->enemy[1]);
	SDL_FreeSurface(hud->ammoicon);
	SDL_FreeSurface(hud->lifeicon);
	free_audio(hud);
	if (hud->arial)
		TTF_CloseFont(hud->arial);
	SDL_FreeSurface(hud->nbammo);
	SDL_FreeSurface(hud->nblife);
	TTF_Quit();
	return (0);
}
