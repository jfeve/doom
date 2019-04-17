/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:41:06 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 19:05:06 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "../libft/libft.h"
# include "defines.h"
# include "def_rend.h"
# include <math.h>
# include "../lib/SDL2.framework/Versions/Current/Headers/SDL.h"
# include "../lib/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../lib/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdio.h>

typedef struct					s_float
{
	float						x;
	float						y;
}								t_float;

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
	t_sec						*hl_sec_temp;
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
void							cancels(t_edit *edit, t_input *in);
void							check_input(t_edit *edit, t_input *in);
void							new_vert(t_edit *edit, t_input *in);
void							update_event(t_input *in);
void							check_event(char *mapname, t_input *in, t_edit *edit);

/*sdl*/

int								free_sdl(t_sdl *sdl, int flag);
int								sdl_init(t_sdl *sdl);
int								display_frame(SDL_Renderer *ren, Uint32 *pix);
void							clear_tab(t_sdl *sdl);

/*bresen*/
void							bresen(t_lis a, t_lis b, t_sdl *sdl);
void                            do_1(int dx, int dy, t_lis *a);
void                            do_2(int dx, int dy, t_lis *a);
void                            do_3(int dx, int dy, t_lis *a);
void                            do_4(int dx, int dy, t_lis *a);

/*vertex*/
int					parse_data(int x, int y, t_edit *edit, t_lis *vert);
void				cancel_last(t_lis **vert);
t_lis				mult_unit(t_lis vert);
t_lis				mult_unit(t_lis vert);
int					arr(int x);
float				arr_float(float x);
t_lis				*create_vert(int x, int y);
int					add_vert(int x, int y, t_edit *edit, t_lis *vert);
void				draw_vert(t_lis *tmp, t_edit *edit);
void				put_vert(t_edit *edit, t_lis *vert);

/*vectors*/
void				draw_vec(t_edit *edit, t_input in);
void				portals(t_edit *edit, t_input *in);
void				put_new_vert(t_edit *edit, t_input *in);
int					vec_here(t_lis *tmp, t_lis*vert, t_point *in);
int					check_coord_in(t_lis *tmp, t_lis *vert, t_point *in, int flag);
void				clear_hl_vec(t_sec *sec);
int					check_on_vec(t_point *in, t_sec *sec);

/*highlight*/
void							hl_vec(t_edit *edit, t_input *in);
void							hl_mode(t_input *in, t_edit *edit);

/*sec*/
void							set_sect(t_edit *edit);
void							draw_sec(t_edit *edit);

/*print*/
void							print_lis(t_lis **vert);
void							print_sec(t_sec *sec);

/*HUD*/
void							set_grid(t_edit *edit);
void							hud(t_edit *edit);

/*objs*/
void							handle_obj(t_edit *edit);
void							handle_enem(t_edit *edit);
void							draw_obj_enem(t_edit *edit);
void							obj(t_edit *edit, t_input *in);
void							enem(t_edit *edit, t_input *in);

/*MapEdit*/
int								check_mapname(char *mapname);
int								map_writer(char *mapname, t_edit *edit);
int								save_map(t_input *in, char *mapname, t_edit *edit);
/*Detection d'Input*/
void							put_zer_flag(t_edit *edit);
void							handle_res(t_edit *edit);
void							draw_num(t_edit *edit, t_draw data, int num);
void							draw_(t_edit *edit, t_draw *draw);
t_draw							write_num(int x, int y, int col);
void							draw_text(t_edit *edit);
void							input_mode(t_input *in, t_edit *edit);

/*rend*/
int					min(int a, int b);
int					max(int a, int b);
int					clamp(int a, int mi, int ma);
int					vxs(int ax, int ay, int bx, int by);
int					overlap(t_point a, t_point b);
int					intersectbox(t_point a, t_point b, t_point c, t_point d);
int					pointside(t_point p, t_point a, t_point b);

float				f_max(float a, float b);
float				f_min(float a, float b);
float				f_clamp(float a, float mi, float ma);
float				f_vxs(float ax, float ay, float bx, float by);
int					f_overlap(t_float a, t_float b);
int					f_intersectbox(t_float a, t_float b, t_float c, t_float d);
float				f_pointside(t_float p, t_float a, t_float b);

#endif
