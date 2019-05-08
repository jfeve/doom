/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 15:40:08 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:41:47 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAPF_H
# define MAPF_H

# define MAX_SECT 128
# define MAX_SPRITE 128

# include "../lib/SDL2.framework/Versions/Current/Headers/SDL.h"
# include "../lib/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../lib/SDL2_mixer.framework/Headers/SDL_mixer.h"

/*
** Render Data
*/

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

typedef struct					s_queue
{
	int							sect;
	int							sx1;
	int							sx2;
}								t_queue;

typedef struct				s_sdl
{
	SDL_Window				*win;
	SDL_Renderer			*ren;
	Uint32					*pix;
	SDL_PixelFormat			*form;
}							t_sdl;

typedef struct				s_enemies
{
	float					x;
	float					y;
	int						life;
	short					type;
	short					sec;
}							t_enemies;

typedef struct				s_objects
{
	int						x;
	int						y;
	short					type;
	short					sec;
	short					picked;
}							t_objs;

typedef struct				s_sprite
{
	int						x;
	int						y;
	int						type;
	float					tx;
	float					tz;
	int						is_enemy;
}							t_sprite;

typedef struct				s_xyz
{
	float					x;
	float					y;
	float					z;
}							t_xyz;

typedef enum				e_state
{
	nmoving,
	moving,
	jumping,
	falling,
	crouching,
	flying,
	running
}							t_state;

typedef struct				s_player
{
	t_xyz					where;
	t_xyz					velo;
	float					angle;
	float					anglesin;
	float					yaw;
	float					anglecos;
	short					sect;
	int						coll;
	t_state					state;
	float					add_z;
	int						jump_sec;
	float					eye;
	int						life;
	int						ammo;
}							t_player;

typedef struct				s_vertex
{
	int						x;
	int						y;
	short					text;
	int						neigh;
	float					texx;
	int						ps;
}							t_vertex;

typedef struct				s_sector
{
	short					floor;
	short					ceil;
	int						nbvert;
	short					nbobjs;
	short					nbenem;
	short					gravity;
	t_vertex				*vert;
	t_objs					*obj;
	t_enemies				*enem;
	float					texy;
	int						lum;
}							t_sector;

typedef struct				s_x
{
	int						tx;
	int						ya;
	int						yb;
	int						cya;
	int						cyb;
	int						nya;
	int						nyb;
	int						cnya;
	int						cnyb;
}							t_x;

typedef struct				s_quad
{
	int						x;
	int						s;
	int						ya;
	int						yb;
}							t_quad;

typedef struct				s_ren
{
	t_x						xx;
	t_queue					queue[MAXQ];
	t_queue					*head;
	t_queue					*tail;
	t_queue					now;
	int						ytop[RWIN_W];
	int						ybot[RWIN_W];
	int						u0;
	int						u1;
	t_float					v1;
	t_float					v2;
	t_float					t1;
	t_float					t2;
	int						x1;
	int						x2;
	t_point					y1;
	t_point					y2;
	t_point					ny1;
	t_point					ny2;
	t_float					org1;
	t_float					org2;
	t_point					u;
	float					yceil;
	float					yfloor;
	int						neigh;
	float					pcos;
	float					psin;
}							t_ren;

typedef struct				s_rendu
{
	int						id;
	int						beginx;
	int						endx;
}							t_rendu;

typedef struct				s_mapf
{
	char					magic[5];
	int						pl_x;
	int						pl_y;
	int						finish_x;
	int						finish_y;
	short					finish_sec;
	short					nbsect;
	short					diff;
	int						nbobjs;
	int						nbenem;
	t_sector				*sectors;
	t_player				player;
	float					coeff;
	t_sdl					sdl;
	t_rendu					rend_s[MAX_SECT];
	short					nbrend_s;
	t_xyz					old;
	SDL_Surface				*wall[4];
	short					has_key;
}							t_mapf;

#endif
