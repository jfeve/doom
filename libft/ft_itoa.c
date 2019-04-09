/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:53 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 00:52:34 by nzenzela    ###    #+. /#+    ###.fr     */
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
	char	*str;

	i = n;
	j = 0;
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
	return (ft_fillstr(str, i, j));
}
