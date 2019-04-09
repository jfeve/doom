/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 11:58:32 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int		map_writer(char *mapname, t_edit *edit)
{
	t_sec	*tmp;
	t_lis	*temp;
	int		fd;
	char	*map_path;
	int		i;
	int		sect_num;

	tmp = edit->sect;
	map_path = (char*)malloc(sizeof(char) * (int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
	ft_strcat(ft_strcat(ft_strcat(map_path, MAP_PATH), mapname), ".mapf");
	i = 1;
	sect_num = 1;
	if((fd = open(map_path,  O_WRONLY | O_APPEND | O_CREAT, 0644)) != -1)
	{
		write(fd, "MAPF", 4);
		if (tmp != NULL)
		{
			while (tmp->next)
			{
				temp = tmp->vert;
				dprintf(1, "\n--------------\n");
				while (temp->next)
				{
					dprintf(1, "Vertex %d : x = %d , y = %d\n", i, temp->x, temp->y);
					temp = temp->next;
					i += 1;
				}
				dprintf(1, "Vertex %d : x = %d , y = %d", i, temp->x, temp->y);
				dprintf(1, "\n--------------\n");
				i = 1;
				sect_num += 1;
				tmp = tmp->next;
			}
			i = 1;
			while (temp->next)
			{
				dprintf(1, "Vertex %d : x = %d , y = %d\n", i, temp->x, temp->y);
				temp = temp->next;
				i += 1;
			}
			dprintf(1, "Vertex %d : x = %d , y = %d\n", i, temp->x, temp->y);
			dprintf(1, "\n--------------\n");
			//
			dprintf(1, "\n -- List of Sectors : %d\n", sect_num);
		}
		return (1);
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
