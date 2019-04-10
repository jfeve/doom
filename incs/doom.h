/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:41:06 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 19:34:08 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "../libft/libft.h"
# include "defines.h"
# include <math.h>
# include <SDL2/SDL.h>
# include <stdio.h>

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_lis
{
	int				x;
	int				y;
	int				col;
	struct s_lis	*next;
}					t_lis;

typedef struct		s_sec
{
	t_lis			*vert;
	unsigned short				text;
	unsigned short				floor;
	unsigned short				ceil;
	t_lis			*enem;
	t_lis			*obj;
	struct s_sec	*next;
}					t_sec;

typedef struct		s_input
{
	SDL_Event		event;
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
}					t_sdl;

typedef struct		s_edit
{
	int				hud_flag;
	t_sec			*hl_sec;
	t_lis			*hl_vert;
	int				nbsect;
	int				hl;
	int				sec;
	t_lis			*vert;
	t_sec			*sect;
	t_sdl			sdl;
	int				err;
	t_lis			*oldvert;
}					t_edit;


/* event */
void				update_event(t_input *in);
void				check_event(char *mapname, t_input *in, t_edit *edit);

/*sdl*/

int					free_sdl(t_sdl *sdl, int flag);
int					sdl_init(t_sdl *sdl);
int					display_frame(SDL_Renderer *ren, Uint32 *pix);
void				clear_tab(t_sdl *sdl);

/*bresen*/
void				bresen(t_lis a, t_lis b, t_sdl *sdl);

/*vertex*/
t_lis				mult_unit(t_lis vert);
int					arr(int x);
float				arr_float(float x);
t_lis				*create_vert(int x, int y);
void				add_vert(int x, int y, t_edit *edit, t_lis *vert);
void				draw_vert(t_lis *tmp, t_edit *edit);
void				put_vert(t_edit *edit, t_lis *vert);

/*vectors*/
int					check_on_vec(t_point *in, t_sec *sec);

/*highlight*/
void				hl_mode(t_input *in, t_edit *edit);

/*sec*/
void				set_sect(t_edit *edit);
void				draw_sec(t_edit *edit);

/*print*/
void				print_lis(t_lis **vert);
void				print_sec(t_sec *sec);

/*HUD*/
void				hud(t_edit *edit);

/*MapEdit*/
int					map_writer(char *mapname, t_edit *edit);
int					save_map(char *mapname, t_edit *edit);
#endif
