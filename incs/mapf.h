/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 15:40:08 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 06:26:24 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAPF_H
# define MAPF_H


/*
** Render Data
*/
typedef struct				s_enemies
{
	int						x;
	int						y;
	int						life;
	int						display;
	short					type;
	short					sec;
}							t_enemies;

typedef struct				s_objects
{
	int						x;
	int						y;
	int						hitbox;
	short					type;
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
	short					sect;
	int						coll;
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
	short					gravity;
	t_vertex				*vert;
}							t_sector;

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
	t_sdl					sdl;
	t_objs					*objects;
	t_enemies				*enemies;
}							t_mapf;

#endif
