/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 15:40:08 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 18:33:50 by flombard    ###    #+. /#+    ###.fr     */
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
