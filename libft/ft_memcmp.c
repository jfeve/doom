/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:55 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:31:55 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *ptr;
	unsigned char *ptr1;

	ptr = (unsigned char*)s1;
	ptr1 = (unsigned char*)s2;
	while (n > 0)
	{
		if (*ptr != *ptr1)
		{
			return ((unsigned char)*ptr - (unsigned char)*ptr1);
		}
		ptr++;
		ptr1++;
		n--;
	}
	return (0);
}
