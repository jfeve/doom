/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 15:25:45 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 15:27:23 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				check_mapname(char *mapname)
{
	int		i;

	i = 0;
	if (ft_strlen(mapname) >= 4)
	{
		while (mapname[i])
			if (ft_isalpha(mapname[i]))
				i++;
		if (i != ((int)ft_strlen(mapname)))
			return (0);
		else
			return (1);
	}
	else
		return (0);
	return (1);
}