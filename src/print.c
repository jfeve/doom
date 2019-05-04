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
	printf( "==========CONTENT==========\n");
	while (tmp)
	{
		printf("cx = %d\tcy = %d\t addr = %p\n", tmp->x, tmp->y, tmp);
		printf("display = %d\tcursor = %d\t trigger = %d\n", tmp->display, tmp->cursor, tmp->trigger);
		printf("title = %s\tcontent = %s\n\n", tmp->c_title, tmp->c_content);
		tmp = tmp->next;
	}
	printf( "========CONTENT END========");
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
	printf("\n----------LIS----------\n");
	while (tmp != NULL)
	{
		printf("x = %d\ty = %d\taddr = %p\n", tmp->x, tmp->y, tmp);
		printf("col = %0x\toldcol = %0x\ttext = %d\n", tmp->col, tmp->oldcol, tmp->text);
		printf("port = %d\tneigh = %d\n", tmp->port, tmp->neigh);
		tmp = tmp->next;
	}
	printf("\n--------LIS END--------\n");
}



void			print_sec(t_sec *sec)
{
	t_sec		*tmp;

	tmp = sec;
	printf("\n\n\n\n\n\n\n\n-------PRINT SEC-------\n");
	if (tmp == NULL)
		printf("No Sector");
	while (tmp != NULL)
	{
		printf("\n||||||||SEC||||||||\n");
		printf("id = %d\n", tmp->id);
		printf("floor = %d\n", tmp->floor);
		printf("ceil = %d\n", tmp->ceil);
		printf("enem = %p\n", tmp->enem);
		printf("obj = %p\n", tmp->obj);
		printf("Nb objets = %d\n", tmp->objscount);
		printf("Nb enems = %d\n", tmp->enemcount);
		printf("Gravity = %d\n", tmp->gravity);
		print_lis(&tmp->vert);
		printf("\n||||||SEC END||||||\n");
		tmp = tmp->next;
	}
	printf("\n-----PRINT SEC END-----\n\n");
}

void			print_read(t_mapf *mapf)
{
	int		i;
	int		k;

	printf( "Header : %s\n", mapf->magic);
	printf( "Player : x = %f\n", mapf->player.where.x);
	printf( "Player : y = %f\n", mapf->player.where.y);
	printf( "Player : Angle = %f\n", mapf->player.angle);
	printf( "Player : Sector = %d\n", mapf->player.sect);
	printf( "Finish : x = %d\n", mapf->finish_x);
	printf( "Finish : y = %d\n", mapf->finish_y);
	printf( "Finish : Sector = %d\n", mapf->finish_sec);
	printf( "Nb sector : %d\n", mapf->nbsect);
	printf( "Num of Bits : %lu\n", (sizeof(float) + sizeof(float)
					+ sizeof(float) + sizeof(short) + sizeof(int) + sizeof(int)
						+ sizeof(short) + sizeof(int)));
	printf( "\n--------\n");
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
			printf( "   X : %d\n", mapf->sectors[i].vert[k].x);
			printf( "   Y : %d\n", mapf->sectors[i].vert[k].y);
			printf( "   Texture : %d\n", mapf->sectors[i].vert[k].text);
			printf( "   Voisins : %d\n", mapf->sectors[i].vert[k].neigh);
			k++;
		}
		i++;
	}
	i = 0;
	if (mapf->nbobjs != 0)
	{
		printf( "\n-------\nList Objects\n");
		while (i < mapf->nbobjs)
		{
			i++;
		}
	}
	i = 0;
	if (mapf->nbenem != 0)
	{
		printf( "\n--------\nList Enemies\n");
		while (i < mapf->nbenem)
		{
			i++;
		}
	}
}
