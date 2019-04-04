/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:32:02 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:32:02 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (needle[i])
		i++;
	if (i == 0)
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		if (haystack[i + j] == needle[j])
		{
			while (haystack[i + j] == needle[j] && needle[j])
			{
				j++;
			}
			if (needle[j] == '\0')
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
