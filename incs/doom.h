/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:41:06 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 20:03:06 by jfeve       ###    #+. /#+    ###.fr     */
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

typedef struct					s_time
{
	unsigned long long			oldtime;
	unsigned long long			time;
}								t_time;

typedef struct					s_edit
{
	t_time						time;
	t_content					*con;
	t_sdl						sdl;
	t_lis						*vert;
	t_sec						*sect;
	t_lis						*player;
	t_lis						*finish;
	int							hud_flag;
	int							dyn_trigger;
	int							input_res;
	int							nbsect;
	int							hl;
	int							sec;
	int							err;
	t_sec						*hl_sec;
	t_lis						*hl_vert;
	t_lis						*oldvert;
	t_sec						*hl_sec_temp;
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
int								check_input(t_edit *edit, t_input *in);
int								new_vert(t_edit *edit, t_input *in);
void							update_event(t_input *in);
int								check_event(char *mapname,
									t_input *in, t_edit *edit);
int								create_player(t_edit *edit, t_input *in);
int								create_finish(t_edit *edit, t_input *in);


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
int								put_new_vert(t_edit *edit, t_input *in);
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
int								choose_set(t_edit *edit);
void							set_trigger(t_edit *edit, int choice, int trig);
void							draw_wf(int x, int y, t_edit *edit);
void							wf_mode(t_input *in, t_edit *edit);
void							set_grid(t_edit *edit);
void							fill_wf(t_edit *edit);
void							hud(t_edit *edit);

/*
** Draw Object-Enemy
*/
void							handle_obj(t_edit *edit);
void							handle_enem(t_edit *edit);
void							draw_obj_enem(t_edit *edit);
int								obj(t_edit *edit, t_input *in);
int								enem(t_edit *edit, t_input *in);
int								check_lis_input(t_lis *vert);

/*
** Map Saver
*/
int								check_mapname(char *mapname);
int								map_writer(char *mapname, t_edit *edit);
int								save_map(t_input *in, char *mapname,
									t_edit *edit);
int								open_error(char **mapfile);
int								save_error(char *mapfile);
int								save_error2(char *error, t_lis *temp);
void							putinfo_sec(int fd, t_lis *temp, t_sec *tmp);
int								save_d(int fd, t_lis *temp);
int								mcheck_pos(t_edit *edit);
int								mcheck_d(t_lis *temp);
int								mcheck_sec(t_sec *tmp);
int								err_map(char *msg, t_lis *temp);
int								save_objs(int fd, t_lis *temp);
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
void							dyn_enter(t_edit *edit,
									t_input *in, t_content *tmp);
void							check_keyboard(t_input *in, t_content *tmp);
void							get_title(t_edit *edit, t_content **con);
void							free_dyn_content(t_content **con);
void							dyn_input(t_edit *edit, t_input *in);
void							fill_str_content(int size,
										char *ret, char *str);
t_content						*create_content(void);
int								add_content(t_edit *edit, char *cont,
										char *title, t_draw draw);
/*
** Live Input
*/
void							edit_input(t_edit *edit);
void							get_string(t_edit *edit, t_draw *draw);
char							*get_content_char(int num);
void							level_editor(char *mapname);
int								init_edit(t_edit *edit);
int								get_update(t_edit *edit,
									t_input *in, char *mapname);
int								init_content(t_edit *edit);
void							hud_hl(t_edit *edit);

/*
** Free
*/
void							free_lis(t_lis **vert);
void							free_sec(t_sec **sec);
int								free_content(t_edit *edit);
/*
**-------------------------------------|
** ------------ Render ----------------|
** ------------------------------------|
** --------- Render Parts -------------|
** ------------------------------------|
*/

typedef struct		s_queue
{
	int				sect;
	int				sx1;
	int				sx2;
}					t_queue;

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
t_float				f_intersect(t_float a, t_float b, t_float c, t_float d);

void				render(char *str);

#endif
