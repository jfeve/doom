/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:32:00 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:32:00 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		i;
	size_t		len;

	d = dst;
	s = src;
	i = size;
	while (i-- != 0 && *d != '\0')
		d++;
	len = d - dst;
	i = size - len;
	if (i == 0)
		return (len + ft_strlen(s));
	while (*s != '\0')
	{
		if (i != 1)
		{
			*d++ = *s;
			i--;
		}
		s++;
	}
	*d = '\0';
	return (len + (s - src));
}
