/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 15:59:24 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int		map_writer(char *mapname, t_edit *edit)
{
	int		fd;
	char	*map_path;
	int		i;
	int		sect_num;

	map_path = (char*)malloc(sizeof(char) * (int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
	ft_strcat(ft_strcat(ft_strcat(map_path, MAP_PATH), mapname), ".mapf");
	i = 1;
	sect_num = 1;
	if((fd = open(map_path,  O_WRONLY | O_APPEND | O_CREAT, 0644)) != -1)
	{
		write(fd, "MAPF", 4);
		if (edit->sect != NULL)
		{
			while (edit->sect->next)
			{
				dprintf(1, "\n--------------\n");
				while (edit->sect->vert->next)
				{
					dprintf(1, "Vertex %d : x = %d , y = %d\n", i, edit->sect->vert->x, edit->sect->vert->y);
					edit->sect->vert = edit->sect->vert->next;
					i += 1;
				}
				dprintf(1, "Vertex %d : x = %d , y = %d", i, edit->sect->vert->x, edit->sect->vert->y);
				dprintf(1, "\n--------------\n");
				i = 1;
				sect_num += 1;
				edit->sect = edit->sect->next;
			}
			i = 1;
			while (edit->sect->vert->next)
			{
				dprintf(1, "Vertex %d : x = %d , y = %d\n", i, edit->sect->vert->x, edit->sect->vert->y);
				edit->sect->vert = edit->sect->vert->next;
				i += 1;
			}
			dprintf(1, "Vertex %d : x = %d , y = %d\n", i, edit->sect->vert->x, edit->sect->vert->y);
			dprintf(1, "\n--------------\n");
			//
			dprintf(1, "\n -- List of Sectors : %d\n", sect_num);
		}
		return (0);
	}
	else
	{
		free(map_path);
		close(fd);
		return 0;
	}
}

// int			vertex_writer()
// {


// }
// int			map_checker()
// {
// 	return (0);
// }

// int			map_parser(int mode, char *mapname)
// {
// 	return (0);
// }

int		save_map(char *mapname, t_edit *edit)
{
	if (!map_writer(mapname, edit))
		return (0);
	return (1);
}