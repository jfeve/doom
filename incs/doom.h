/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:41:06 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 14:51:16 by nzenzela    ###    #+. /#+    ###.fr     */
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
	int							x;
	int							y;
	int							col;
	int							oldcol;
	int							port;
	short						text;
	int							neigh;
	struct s_lis				*next;
}								t_lis;

typedef struct					s_sec
{
	unsigned short				id;
	short						floor;
	short						ceil;
	t_lis						*vert;
	t_lis						*enem;
	t_lis						*obj;
	struct s_sec				*next;
}								t_sec;

typedef struct					s_input
{
	int							x;
	int							y;
	int							xrel;
	int							yrel;
	int							xwheel;
	int							ywheel;
	SDL_Event					event;
	SDL_bool					key[SDL_NUM_SCANCODES];
	SDL_bool					quit;
	SDL_bool					mouse[6];
}								t_input;

typedef struct					s_sdl
{
	SDL_Window					*win;
	SDL_Renderer				*ren;
	Uint32						*pix;
	SDL_PixelFormat				*form;
}								t_sdl;

typedef	struct					s_draw
{
	char						*input;
	int							x;
	int							y;
	int							x_s;
	int							y_s;
	int							i;
	unsigned	int				color;
}								t_draw;

typedef	struct					s_content
{
	int							x;
	int							y;
	t_draw						draw;
	int							display;
	int							cursor;
	int							trigger;
	char						c_title[256];
	char						c_content[2048];
	struct s_content			*next;
}								t_content;

typedef struct					s_edit
{
	int							hud_flag;
	int							dyn_trigger;
	int							input_res;
	int							nbsect;
	int							hl;
	int							sec;
	int							err;
	t_content					*con;
	t_lis						*player;
	t_lis						*finish;
	t_lis						*vert;
	t_sec						*sect;
	t_sdl						sdl;
	t_sec						*hl_sec;
	t_lis						*hl_vert;
	t_lis						*oldvert;
}								t_edit;

typedef	struct					s_bresen
{
	int							dx;
	int							dy;
	t_lis						*a;
	t_lis						*b;
	t_sdl						*sdl;
}								t_bresen;

/*
** Event
*/
void							cancels(t_edit *edit, t_input *in);
void							check_input(t_edit *edit, t_input *in);
void							new_vert(t_edit *edit, t_input *in);
void							update_event(t_input *in);
void							check_event(char *mapname,
									t_input *in, t_edit *edit);
void							create_player(t_edit *edit, t_input *in);
void							create_finish(t_edit *edit, t_input *in);


/*
** SDL
*/
int								free_sdl(t_sdl *sdl, int flag);
int								sdl_init(t_sdl *sdl);
int								display_frame(SDL_Renderer *ren, Uint32 *pix);
void							clear_tab(t_sdl *sdl);

/*
** Bresen Functions
*/
void							bresen(t_lis a, t_lis b, t_sdl *sdl);
void							do_1(t_bresen *brs);
void							do_2(t_bresen *brs);
void							do_3(t_bresen *brs);
void							do_4(t_bresen *brs);
/*
** Vertex
*/
int								parse_data(int x, int y, t_edit
									*edit, t_lis *vert);
void							cancel_last(t_lis **vert);
t_lis							mult_unit(t_lis vert);
int								arr(int x);
float							arr_float(float x);
t_lis							*create_vert(int x, int y);
int								add_vert(int x, int y, t_edit *edit,
									t_lis *vert);
void							draw_vert(t_lis *tmp, t_edit *edit);
void							put_vert(t_edit *edit, t_lis *vert);

/*
** Vector
*/
void							draw_vec(t_edit *edit, t_input in);
void							portals(t_edit *edit, t_input *in);
void							put_new_vert(t_edit *edit, t_input *in);
int								vec_here(t_lis *tmp, t_lis*vert, t_point *in);
int								check_coord_in(t_lis *tmp, t_lis *vert,
									t_point *in, int flag);
void							clear_hl_vec(t_sec *sec);
int								check_on_vec(t_point *in, t_sec *sec);

/*
** Highlight
*/
void							hl_vec(t_edit *edit, t_input *in);
void							hl_mode(t_input *in, t_edit *edit);

/*
** Sectors
*/
void							set_sect(t_edit *edit);
void							draw_sec(t_edit *edit);

/*
** Print
*/
void							print_info(t_edit *edit, t_input *in);
void							print_content(t_edit *edit);
void							print_lis(t_lis **vert);
void							print_sec(t_sec *sec);

/*
** HUD
*/
void							set_grid(t_edit *edit);
void							hud(t_edit *edit);

/*
** Draw Object-Enemy
*/
void							handle_obj(t_edit *edit);
void							handle_enem(t_edit *edit);
void							draw_obj_enem(t_edit *edit);
void							obj(t_edit *edit, t_input *in);
void							enem(t_edit *edit, t_input *in);
int								check_lis_input(t_lis *vert);

/*
** Map Saver
*/
int								check_mapname(char *mapname);
int								map_writer(char *mapname, t_edit *edit);
int								save_map(t_input *in, char *mapname,
									t_edit *edit);
/*
** Input Detection
*/
void							put_zer_flag(t_edit *edit);
void							handle_res(t_edit *edit);
void							edit_mode(t_input *in, t_edit *edit);

/*
** Drawer
*/
char							*check_spe(int num);
char							*check_num(int num);
char							*check_alpha1(int num);
char							*check_alpha2(int num);
char							*check_alpha3(int num);
void							draw_square(t_edit *edit, t_draw *draw);
void							prepare_draw(t_edit *edit);
t_draw							init_draw(int x, int y, int disp);
void							draw_norm(t_draw *cnt, t_draw *draw,
										t_edit *ed, char *tmp);
void							draw_checks(char c, t_draw *cnt, t_draw *draw);

/*
** Contents
*/
void							dyn_input(t_edit *edit, t_input *in);
void							fill_str_content(int size,
										char *ret, char *str);
t_content						*create_content(void);
void							add_content(t_edit *edit, char *cont,
										char *title, t_draw draw);
/*
** Live Input
*/
void							edit_input(t_edit *edit);
void							get_string(t_edit *edit, t_draw *draw);
char							*get_content_char(int num);
void							level_editor(char *mapname);
int								init_edit(t_edit *edit);
void							get_update(t_edit *edit,
									t_input *in, char *mapname);
void							init_content(t_edit *edit);
void							hud_hl(t_edit *edit);

#endif
