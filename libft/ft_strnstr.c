/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:32:02 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 00:52:04 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return ((char*)haystack);
	i = 0;
	while (i < len && haystack[i] && needle[j])
	{
		if (haystack[i + j] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < len && needle[j])
			{
				j++;
			}
			if (needle[j] == '\0')
				return ((char*)haystack + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
