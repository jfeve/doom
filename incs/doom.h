/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:41:06 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 20:02:30 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "../libft/libft.h"
# include "defines.h"
# include <math.h>
# include "../lib/SDL2.framework/Versions/Current/Headers/SDL.h"
# include "../lib/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../lib/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdio.h>

typedef struct					s_point
{
	int							x;
	int							y;
}								t_point;

typedef struct					s_lis
{
	int				x;
	int				y;
	int				col;
	int				oldcol;
	int				port;
	short			text;
	int				neigh;
	struct s_lis	*next;
}					t_lis;

typedef struct					s_sec
{
	t_lis			*vert;
	unsigned short	id;
	short	floor;
	short	ceil;
	t_lis			*enem;
	t_lis			*obj;
	struct s_sec	*next;
}					t_sec;

typedef struct					s_input
{
	SDL_Event					event;
	SDL_bool					key[SDL_NUM_SCANCODES];
	SDL_bool					quit;
	int							x;
	int							y;
	int							xrel;
	int							yrel;
	int							xwheel;
	int							ywheel;
	SDL_bool					mouse[6];
}								t_input;

typedef struct					s_sdl
{
	SDL_Window					*win;
	SDL_Renderer				*ren;
	Uint32						*pix;
	SDL_PixelFormat				*form;
}								t_sdl;

typedef struct					s_edit
{
	int							input_res;
	int							input_flag;
	int							input_trigger;
	char						input_list[9];
	int							input_cursor;
	int							hud_flag;
	t_sec						*hl_sec;
	t_lis						*hl_vert;
	int							nbsect;
	int							hl;
	int							sec;
	t_lis						*player;
	t_lis						*vert;
	t_sec						*sect;
	t_sdl						sdl;
	int							err;
	t_lis						*oldvert;
}								t_edit;

typedef	struct					s_draw
{
	char						*input;
	int							x;
	int							y;
	int							x_s;
	int							y_s;
	int 						i;
	unsigned	int				color;
}								t_draw;

/* event */
void							update_event(t_input *in);
void							check_event(char *mapname, t_input *in, t_edit *edit);

/*sdl*/

int								free_sdl(t_sdl *sdl, int flag);
int								sdl_init(t_sdl *sdl);
int								display_frame(SDL_Renderer *ren, Uint32 *pix);
void							clear_tab(t_sdl *sdl);

/*bresen*/
void							bresen(t_lis a, t_lis b, t_sdl *sdl);

/*vertex*/
int					parse_data(int x, int y, t_edit *edit, t_lis *vert);
void				cancel_last(t_lis **vert);
t_lis				mult_unit(t_lis vert);
int					arr(int x);
float				arr_float(float x);
t_lis				*create_vert(int x, int y);
int					add_vert(int x, int y, t_edit *edit, t_lis *vert);
void				draw_vert(t_lis *tmp, t_edit *edit);
void				put_vert(t_edit *edit, t_lis *vert);

/*vectors*/
void				portals(t_edit *edit, t_input *in);
void				put_new_vert(t_edit *edit, t_input *in);
int					vec_here(t_lis *tmp, t_lis*vert, t_point *in);
int					check_coord_in(t_lis *tmp, t_lis *vert, t_point *in, int flag);
void				clear_hl_vec(t_sec *sec);
int					check_on_vec(t_point *in, t_sec *sec);

/*highlight*/
void							hl_mode(t_input *in, t_edit *edit);

/*sec*/
void							set_sect(t_edit *edit);
void							draw_sec(t_edit *edit);

/*print*/
void							print_lis(t_lis **vert);
void							print_sec(t_sec *sec);

/*HUD*/
void							hud(t_edit *edit);

/*MapEdit*/
int								map_writer(char *mapname, t_edit *edit);
int								save_map(t_input *in, char *mapname, t_edit *edit);
/*Detection d'Input*/
void							draw_num(t_edit *edit, t_draw data, int num);
void							draw_(t_edit *edit, t_draw *draw);
t_draw							write_num(int x, int y, int col);
void							draw_text(t_edit *edit);
void							input_mode(t_input *in, t_edit *edit);
#endif
