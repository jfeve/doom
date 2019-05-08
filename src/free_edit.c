/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_edit.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:13:18 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 20:13:48 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void	free_lis(t_lis **vert)
{
	t_lis		*curr;
	t_lis		*tmp;

	curr = *vert;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*vert = NULL;
}

void	free_sec(t_sec **sec)
{
	t_sec		*curr;
	t_sec		*tmp;

	curr = *sec;
	while (curr)
	{
		tmp = curr->next;
		if (curr->vert)
			free_lis(&curr->vert);
		if (curr->obj)
			free_lis(&curr->obj);
		if (curr->enem)
			free_lis(&curr->enem);
		free(curr);
		curr = tmp;
	}
	*sec = NULL;
}

void	free_all(int flag, t_edit *edit)
{
	if (flag >= 1)
		free_content(edit);
	if (flag >= 2)
		free_sdl(&edit->sdl, 6);
	if (edit->vert)
		free_lis(&edit->vert);
	if (edit->sect)
		free_sec(&edit->sect);
	if (edit->player)
		free_lis(&edit->player);
	if (edit->finish)
		free_lis(&edit->finish);
	edit->hl_sec = NULL;
	edit->hl_vert = NULL;
	edit->oldvert = NULL;
	edit->hl_sec_temp = NULL;
}

void	free_mapf(t_mapf *mapf)
{
	int		i;

	i = -1;
	while (++i < 4)
		if (mapf->wall[i])
			SDL_FreeSurface(mapf->wall[i]);
	i = -1;
	while (++i < mapf->nbsect)
	{
		if (mapf->sectors[i].vert)
			free(mapf->sectors[i].vert);
		if (mapf->sectors[i].enem)
			free(mapf->sectors[i].enem);
		if (mapf->sectors[i].obj)
			free(mapf->sectors[i].obj);
	}
	if (mapf->sectors)
		free(mapf->sectors);
}
