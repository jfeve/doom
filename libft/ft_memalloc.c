/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:54 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:31:54 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (!(ptr = malloc(sizeof(unsigned char) * (size))))
		return (NULL);
	while (i <= size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
