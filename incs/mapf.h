/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 15:40:08 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 13:00:08 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAPF_H
# define MAPF_H


/*
** Coucou
*/
typedef struct				s_enemies
{
	int						x;
	int						y;
	int						life;
	int						display;
	int						type;
	short					sec;
}							t_enemies;

typedef struct				s_objects
{
	int						x;
	int						y;
	int						type;
	int						hitbox;
	short					sec;
}							t_objs;

typedef struct				s_xyz
{
	float					x;
	float					y;
	float					z;
}							t_xyz;

typedef struct				s_player
{
	t_xyz					where;
	t_xyz					velo;
	float					angle;
	float					anglesin;
	float					yaw;
	float					anglecos;
	unsigned				sect;
}							t_player;

typedef struct				s_vertex
{
	int						x;
	int						y;
	short					text;
	int						neigh;
}							t_vertex;

typedef struct				s_sector
{
	short					floor;
	short					ceil;
	int						nbvert;
	short					nbobjs;
	short					nbenem;
	t_vertex				*vert;
}							t_sector;

typedef struct				s_mapf
{
	char					magic[5];
	int						finish_x;
	int						finish_y;
	short					finish_sec;
	short					nbsect;
	short					diff;
	t_sector				*sectors;
	t_player				player;
	t_sdl					sdl;
	t_objs					*objects;
	t_enemies				*enemies;
}							t_mapf;

#endif
