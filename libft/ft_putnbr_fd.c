/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:57 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:31:57 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long lg;
	char a;

	lg = n;
	a = '0';
	if (lg < 0)
	{
		write(fd, "-", 1);
		lg = -lg;
	}
	if (lg >= 0 && lg <= 9)
	{
		a = a + lg;
		write(fd, &a, 1);
	}
	else
	{
		ft_putnbr_fd(lg / 10, fd);
		ft_putnbr_fd(lg % 10, fd);
	}
}
