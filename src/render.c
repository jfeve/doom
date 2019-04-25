/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:37:33 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 16:14:59 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*static int	render_event(t_input *in)
{
	;
}*/

static void	pre_draw(t_render *r, t_sdl *sdl)
{
	int			ytop[WIN_W];
	int			ybot[WIN_W];
	unsigned int	i;

	i = 0;
	while (i < WIN_W)
	{
		ytop[i] = 0;
		ybot[i] = WIN_H - 1;
		i++;
	}
	i = 0;
	while (i < r->s.nbpts)
	{
		;
		i++;
	}
}

static int	render_update(t_render *r, t_sdl *sdl, t_input *in)
{
	update_event(in);
	(void)sdl;
	pre_draw(r, sdl);
	return (1);
}

void		render(void)
{
	t_sdl		sdl;
	t_input		in;
	t_render	r;

/**/
r.p = (t_player){20, 20, 6, 0};
r.sects = (t_sector){0, 20, {{0, 0}, {0, 50}, {50, 50}, {50, 0}}, 4, {-1, -1, -1, -1}};
/**/

	ft_bzero(&in, sizeof(t_input));
	if (!sdl_init(&sdl))
		return ;
	while (!in.quit)
	{
		if (render_update(&r, &sdl, &in) == 0)
			break ;
		if (display_frame(sdl.ren, sdl.pix) == 0)
			break ;
		SDL_Delay(1000 / 60);
	}
	free_sdl(&sdl, 6);
}
