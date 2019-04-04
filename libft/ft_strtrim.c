/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:32:03 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 19:32:03 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_fillstr(char *str, char const *s, int j, int i)
{
	int		k;

	k = 0;
	while (k < j)
	{
		str[k] = s[i + k];
		k++;
	}
	str[k] = '\0';
	return (str);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[i + j])
		j++;
	while (s[i + j - 1] == ' ' || s[i + j - 1] == '\n' || s[i + j - 1] == '\t')
		j--;
	if (j < 0)
		j = 0;
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	return (ft_fillstr(str, s, j, i));
}
