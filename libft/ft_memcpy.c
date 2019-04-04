/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:55 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:31:55 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *ptr;
	unsigned char *ptr1;

	ptr = (unsigned char*)dst;
	ptr1 = (unsigned char*)src;
	while (n > 0)
	{
		*ptr = *ptr1;
		ptr++;
		ptr1++;
		n--;
	}
	return (dst);
}
