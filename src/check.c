/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 15:25:45 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 13:27:48 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int			check_mapname(char *mapname)
{
	int		i;

	i = 0;
	if (ft_strlen(mapname) >= 4)
	{
		while (mapname[i])
			if (ft_isalpha(mapname[i]))
				i++;
			else
				i--;
		if (i != ((int)ft_strlen(mapname)))
			return (0);
		else
			return (1);
	}
	else
		return (0);
	return (1);
}

int			check_color(int c)
{
	if (c == 1)
		return (RED);
	else if (c == 2)
		return (CYAN);
	else if (c == 3)
		return (GREEN);
	else if (c == 4)
		return (DARK);
	else
		return (WHITE);
}

char		*check_spe(int num)
{
	if (num == 58)
		return (_POINT_);
	if (num == 74)
		return (_CURSOR_);
	else if (num == 61)
		return (_EQUAL_);
	else if (num == 47)
		return (_SLASH_);
	else if (num == ',')
		return (_COMMA_);
	else if (num == ' ')
		return ("\t\0");
	else
		return ("\0");
}
