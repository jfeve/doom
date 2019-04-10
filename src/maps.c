/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 15:14:10 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 16:23:58 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static	int				putinfo_head(int fd, t_edit *edit, unsigned short count_sect)
{
	float				player_pos_x = 5.0;
	float				player_pos_y = 15.0;
	unsigned short		player_pos_s = 0;

	if (fd == -1)
		return (0);
	write(fd, "MAPF", 4);
	if (count_sect != 0)
	{
		if (edit->sec)
		{
			
		}
		write(fd, &player_pos_x, sizeof(float));
		write(fd, &player_pos_y, sizeof(float));
		write(fd, &player_pos_s, sizeof(unsigned short));
		write(fd, &count_sect, sizeof(unsigned short));
		return (1);
	}
	else
		return (0);	
}

static	int				putinfo_sector(int fd, t_edit *edit, unsigned short count_sect)
{
	t_sec		*tmp;
	t_lis		*temp;
	int			i;
	int			sect;

	sect = 1;
	i = 1;
	if (fd == -1)
		return (0);
	tmp = edit->sect;
	while (tmp != NULL)
	{
		temp = tmp->vert;
		while (temp != NULL)
		{
			dprintf(1, "Sector %d || Vertex %d : x = %d , y = %d\n", i,sect, temp->x, temp->y);
			temp = temp->next;
			i += 1;
		}
		i = 1;
		sect += 1;
		tmp = tmp->next;
	}
	dprintf(1, "\n -- List of Sectors : %d\n", count_sect);
	return (1);
}

int						map_writer(char *mapname, t_edit *edit)
{
	int					fd;
	char				*mapfile;
	unsigned short		sect_num;

	mapfile = (char*)malloc(sizeof(char) * (int)ft_strlen(MAP_PATH) + (int)ft_strlen(mapname) + 2);
	ft_strcat(ft_strcat(ft_strcat(mapfile, MAP_PATH), mapname), ".mapf");
	if((fd = open(mapfile, O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU)) != -1)
	{
		sect_num = count_sector(edit);
		if (sect_num != 0)
		{
			putinfo_head(fd, edit, sect_num);
			putinfo_sector(fd, edit, sect_num);
			close(fd);
			return (1);
		}
		else
		{
			free(mapfile);
			close(fd);
			return (0);
		}
	}
	else
	{
		dprintf(1,"We could not open the file");
		free(mapfile);
		close(fd);
		return (0);
	}
}

int		save_map(char *mapname, t_edit *edit)
{
	if (!map_writer(mapname, edit))
		return (0);
	return (1);
}