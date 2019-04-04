/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:55 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:31:55 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *ptr;
	unsigned char *ptr1;
	unsigned char c_cpy;

	ptr = (unsigned char*)dst;
	ptr1 = (unsigned char*)src;
	c_cpy = (unsigned char)c;
	while (n > 0)
	{
		*ptr = *ptr1;
		if (*ptr == c_cpy)
		{
			ptr++;
			return (ptr);
		}
		ptr++;
		ptr1++;
		n--;
	}
	return (NULL);
}
