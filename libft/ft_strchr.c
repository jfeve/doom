/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:58 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:31:58 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	a;

	i = 0;
	a = c;
	while (s[i])
	{
		if (s[i] == a)
			return ((char*)s + i);
		i++;
	}
	if (s[i] == a)
		return ((char*)s + i);
	return (NULL);
}
