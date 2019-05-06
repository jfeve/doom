/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sdl.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:40:34 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 20:37:19 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				free_sdl(t_sdl *sdl, int flag)
{
	if (flag >= 1)
		SDL_Quit();
	if (flag >= 2)
		SDL_DestroyWindow(sdl->win);
	if (flag >= 3)
		SDL_DestroyRenderer(sdl->ren);
	if (flag >= 4)
		free(sdl->pix);
	if (flag >= 5)
		SDL_FreeFormat(sdl->form);
	return (0);
}

int				sdl_init(t_sdl *sdl, int w, int h)
{
	int			i;

	i = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (free_sdl(sdl, 1));
	sdl->win = SDL_CreateWindow("Doom-Nukem", 100, 100, w, h,
			SDL_WINDOW_ALWAYS_ON_TOP); 
	if (sdl->win == NULL)
		return (free_sdl(sdl, 1));
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (sdl->ren == NULL)
		return (free_sdl(sdl, 2));
	if (!(sdl->pix = malloc(sizeof(Uint32) * (w * h))))
		return (free_sdl(sdl, 3));
	sdl->form = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	if (sdl->form == NULL)
		return (free_sdl(sdl, 4));
	return (1);
}

int				display_frame(SDL_Renderer *ren, Uint32 *pix, int w, int h)
{
	SDL_Texture *tex;

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(ren);
	tex = SDL_CreateTexture(ren, PIXFOR,
		SDL_TEXTUREACCESS_STREAMING, w, h);
	SDL_UpdateTexture(tex, NULL, (void*)pix, sizeof(Uint32) * w);
	if (tex == NULL)
		return (0);
	if (SDL_RenderCopy(ren, tex, NULL, NULL) != 0)
		return (0);
	SDL_RenderPresent(ren);
	SDL_DestroyTexture(tex);
	return (1);
}

void			clear_tab(t_sdl *sdl, int w, int h)
{
	int x;
	int y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			sdl->pix[y * w + x] = 0x000000FF;
			x++;
		}
		y++;
	}
}
