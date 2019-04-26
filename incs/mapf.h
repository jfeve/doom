/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 15:40:08 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 20:00:18 by nzenzela    ###    #+. /#+    ###.fr     */
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
	int						type;
	short					sec;
	struct s_enemies		*next;
}							t_enemies;

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
	t_sector				*sectors;
}							t_mapf;

#endif
