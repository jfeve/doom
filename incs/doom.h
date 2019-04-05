/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:41:06 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 16:10:44 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "../libft/libft.h"
# include <math.h>
# include <SDL2/SDL.h>
# define WIN_W 1500
# define WIN_H 1000
# define PIXFOR SDL_PIXELFORMAT_RGBA8888
# define SDL_BUTTON_LEFT 1
# define SDL_BUTTON_MIDDLE 2
# define SDL_BUTTON_RIGHT 3
# define SDL_BUTTON_X1 4
# define SDL_BUTTON_X2 5
# define WHITE 0xFFFFFFFF

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_lis
{
	int				x;
	int				y;
	struct s_lis	*next;
}					t_lis;

typedef struct		s_input
{
	SDL_bool		key[SDL_NUM_SCANCODES];
	SDL_bool		quit;
	int				x;
	int				y;
	int				xrel;
	int				yrel;
	int				xwheel;
	int				ywheel;
	SDL_bool		mouse[6];
}					t_input;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	Uint32			*pix;
	SDL_PixelFormat	*form;
	int				color;
}					t_sdl;

typedef struct		s_edit
{
	t_sdl			sdl;
	int				err;
}					t_edit;


/* event */
void				update_event(t_input *in);
void				check_event(t_input *in, t_lis **vert);

/*sdl*/

int					free_sdl(t_sdl *sdl, int flag);
int					sdl_init(t_sdl *sdl);
int					display_frame(SDL_Renderer *ren, Uint32 *pix);

/*trace*/
void				ft_bresen(t_point a, t_point b, t_sdl *sdl);
int					ft_value_e(int dx, int dy);
void				ft_dx_zero(int x1, int y1, int y2, t_sdl *sdl);
void				ft_dy_zero(int x1, int y1, int x2, t_sdl *sdl);
void				ft_pixel(int x, int y, t_sdl *sdl);

/*printf*/
void				print_lis(t_lis **vert);
#endif
