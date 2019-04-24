/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:37:33 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 13:48:17 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static int	render_event(t_input *in)
{
	;
}

static int	render_update(t_sdl *sdl, t_input *in)
{
	update_event(in);
}

void		render(void)
{
	t_sdl		sdl;
	t_input		in;

	ft_bzero(&in, sizeof(t_input));
	if (!sdl_init(&sdl))
		return ;
	while (!in.quit)
	{
		if (render_update(&sdl, &in) == 0)
			break ;
		if (display_frame(sdl.ren, sdl.pix) == 0)
			break ;
		SDL_Delay(1000 / 60);
	}
	free_sdl(&sdl, 6);
}
