/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 21:32:10 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 14:33:04 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			print_content(t_edit *edit)
{
	t_content	*tmp;

	tmp = edit->con;
	dprintf(1, "==========CONTENT==========\n");
	while (tmp)
	{
		dprintf(1, "cx = %d\tcy = %d\t addr = %p\n", tmp->x, tmp->y, tmp);
		dprintf(1, "display = %d\tcursor = %d\t trigger = %d\n", tmp->display, tmp->cursor, tmp->trigger);
		dprintf(1, "title = %s\tcontent = %s\n\n", tmp->c_title, tmp->c_content);
		tmp = tmp->next;
	}
	dprintf(1, "========CONTENT END========");
}

void			print_info(t_edit *edit, t_input *in)
{
	if (in->key[SDL_SCANCODE_G])
	{
		print_content(edit);
		print_sec(edit->sect);
		in->key[SDL_SCANCODE_G] = SDL_FALSE;
	}
}

void			print_lis(t_lis **vert)
{
	t_lis		*tmp;

	tmp = *vert;
	dprintf(1, "\n----------LIS----------\n");
	while (tmp != NULL)
	{
		dprintf(1, "x = %d\ty = %d\taddr = %p\n", tmp->x, tmp->y, tmp);
		dprintf(1, "col = %0x\toldcol = %0x\ttext = %d\n", tmp->col, tmp->oldcol, tmp->text);
		dprintf(1, "port = %d\tneigh = %d\n", tmp->port, tmp->neigh);
		tmp = tmp->next;
	}
	dprintf(1, "\n--------LIS END--------\n");
}



void			print_sec(t_sec *sec)
{
	t_sec		*tmp;

	tmp = sec;
	dprintf(1, "\n\n\n\n\n\n\n\n-------PRINT SEC-------\n");
	if (tmp == NULL)
		dprintf(1, "No Sector");
	while (tmp != NULL)
	{
		dprintf(1, "\n||||||||SEC||||||||\n");
		dprintf(1, "id = %d\n", tmp->id);
		dprintf(1, "floor = %d\n", tmp->floor);
		dprintf(1, "ceil = %d\n", tmp->ceil);
		dprintf(1, "enem = %p\n", tmp->enem);
		dprintf(1, "obj = %p\n", tmp->obj);
		dprintf(1, "Nb objets = %d\n", tmp->objscount);
		dprintf(1, "Nb enems = %d\n", tmp->enemcount);
		print_lis(&tmp->vert);
		dprintf(1, "\n||||||SEC END||||||\n");
		tmp = tmp->next;
	}
	dprintf(1, "\n-----PRINT SEC END-----\n\n");
}

void			print_read(t_mapf *mapf)
{
	int		i;
	int		k;

	dprintf(1, "Header : %s\n", mapf->magic);
	dprintf(1, "Player : x = %f\n", mapf->player.where.x);
	dprintf(1, "Player : y = %f\n", mapf->player.where.y);
	dprintf(1, "Player : Angle = %f\n", mapf->player.angle);
	dprintf(1, "Player : Sector = %d\n", mapf->player.sect);
	dprintf(1, "Finish : x = %d\n", mapf->finish_x);
	dprintf(1, "Finish : y = %d\n", mapf->finish_y);
	dprintf(1, "Finish : Sector = %d\n", mapf->finish_sec);
	dprintf(1, "Nb sector : %d\n", mapf->nbsect);
	dprintf(1, "Num of Bits : %lu\n", (sizeof(float) + sizeof(float)
					+ sizeof(float) + sizeof(short) + sizeof(int) + sizeof(int)
						+ sizeof(short) + sizeof(int)));
	dprintf(1, "\n--------\n");
	i = 0;
	k = 0;
	while (i < mapf->nbsect)
	{
		dprintf(1, "OBJ = %d\n", mapf->sectors[i].nbobjs);
		dprintf(1, "obj = %p\n", mapf->sectors[i].obj);
		dprintf(1, "Sector : %d\n", i);
		dprintf(1, " Gravity : %d\n", mapf->sectors[i].gravity);
		dprintf(1, " Floor : %d\n", mapf->sectors[i].floor);
		dprintf(1, " Ceil : %d\n", mapf->sectors[i].ceil);
		dprintf(1, " Nb Vertex %d\n", mapf->sectors[i].nbvert);
		dprintf(1, " Nb Objs %d\n", mapf->sectors[i].nbobjs);
		dprintf(1, " Nb Enem %d\n", mapf->sectors[i].nbenem);
		k = 0;
		while (k < mapf->sectors[i].nbvert)
		{
			dprintf(1, "   X : %d\n", mapf->sectors[i].vert[k].x);
			dprintf(1, "   Y : %d\n", mapf->sectors[i].vert[k].y);
			dprintf(1, "   Texture : %d\n", mapf->sectors[i].vert[k].text);
			dprintf(1, "   Voisins : %d\n", mapf->sectors[i].vert[k].neigh);
			k++;
		}
		i++;
	}
	i = 0;
	if (mapf->nbobjs != 0)
	{
		dprintf(1, "\n-------\nList Objects\n");
		while (i < mapf->nbobjs)
		{
			i++;
		}
	}
	i = 0;
	if (mapf->nbenem != 0)
	{
		dprintf(1, "\n--------\nList Enemies\n");
		while (i < mapf->nbenem)
		{
			i++;
		}
	}
}
