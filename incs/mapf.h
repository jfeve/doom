/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 15:40:08 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 20:21:30 by nzenzela    ###    #+. /#+    ###.fr     */
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
	unsigned	int			life;
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
	t_vertex				*vert;
}							t_sector;

typedef struct				s_mapf
{
	char					magic[5];
	int						pl_x;
	int						pl_y;
	short					pl_sec;
	int						finish_x;
	int						finish_y;
	short					finish_sec;
	short					nbsect;
	short					nbobjs;
	short					nbenem;
	short					diff;
	t_sector				*sectors;
	t_enemies				*enemies;
	t_objs					*objects;
	t_player				
}							t_mapf;

#endif
