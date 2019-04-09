/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 15:20:51 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int        map_writer(char *mapname, t_edit *edit)
{
    t_sec		*tmp;
    t_lis		*temp;
    int			fd;
    char		*map_path;
    int			i;
    int			sect_num;

    tmp = edit->sect;
    map_path = (char*)malloc(sizeof(char) * (int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
    ft_strcat(ft_strcat(ft_strcat(map_path, MAP_PATH), mapname), ".mapf");
    i = 1;
    sect_num = 0;
    if((fd = open(map_path,  O_WRONLY | O_APPEND | O_CREAT, 0644)) != -1)
    {
        write(fd, "MAPF", 4);
        if (tmp != NULL)
        {
            while (tmp != NULL)
            {
                temp = tmp->vert;
                dprintf(1, "\n--------------\n");
                while (temp != NULL)
                {
                    dprintf(1, "Vertex %d : x = %d , y = %d\n", i, temp->x, temp->y);
                    temp = temp->next;
                    i += 1;
                }
                dprintf(1, "\n--------------\n");
                i = 1;
                sect_num += 1;
                tmp = tmp->next;
            }
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

int		save_map(char *mapname, t_edit *edit)
{
	if (!map_writer(mapname, edit))
		return (0);
	return (1);
}