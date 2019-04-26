/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sdl.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:40:34 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 20:19:34 by jfeve       ###    #+. /#+    ###.fr     */
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

int				sdl_init(t_sdl *sdl)
{
	int			i;

	i = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0);
	sdl->win = SDL_CreateWindow("Doom-Nukem", 100, 100, WIN_W, WIN_H,
			SDL_WINDOW_ALWAYS_ON_TOP);
	if (sdl->win == NULL)
		return (free_sdl(sdl, 1));
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (sdl->ren == NULL)
		return (free_sdl(sdl, 2));
	if (!(sdl->pix = malloc(sizeof(Uint32) * (WIN_W * WIN_H))))
		return (free_sdl(sdl, 3));
	sdl->form = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	if (sdl->form == NULL)
		return (free_sdl(sdl, 4));
	return (1);
}

int				display_frame(SDL_Renderer *ren, Uint32 *pix)
{
	SDL_Texture *tex;

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(ren);
	tex = SDL_CreateTexture(ren, PIXFOR,
		SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	SDL_UpdateTexture(tex, NULL, (void*)pix, sizeof(Uint32) * WIN_W);
	if (tex == NULL)
		return (0);
	if (SDL_RenderCopy(ren, tex, NULL, NULL) != 0)
		return (0);
	SDL_RenderPresent(ren);
	SDL_DestroyTexture(tex);
	return (1);
}

void			clear_tab(t_sdl *sdl)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			sdl->pix[y * WIN_W + x] = 0x000000FF;
			x++;
		}
		y++;
	}
}
