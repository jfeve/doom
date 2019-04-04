/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:53 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:31:53 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		ft_lennbr(long n)
{
	int j;

	j = 0;
	if (n < 0)
		j++;
	while (n != 0)
	{
		n /= 10;
		j++;
	}
	return (j);
}

static char		*ft_fillstr(char *str, long n, int j)
{
	int k;

	k = j - 1;
	while (k >= 0 && n != 0)
	{
		str[k] = (n % 10) + 48;
		n /= 10;
		k--;
	}
	str[j] = '\0';
	return (str);
}

char			*ft_itoa(int n)
{
	long	i;
	int		j;
	int		k;
	char	a;
	char	*str;

	i = n;
	j = 0;
	k = 0;
	a = '0';
	if (n == 0 || n == -0)
		return (ft_strdup("0"));
	j = ft_lennbr(i);
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	i = n;
	if (n < 0)
	{
		str[0] = '-';
		i = -i;
	}
	k = j - 1;
	return (ft_fillstr(str, i, j));
}
