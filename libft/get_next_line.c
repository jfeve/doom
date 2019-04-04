/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:23:10 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2018/01/29 14:17:28 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char **s1, char *s2)
{
	char *str;

	if (!(str = malloc(ft_strlen(*s1) + ft_strlen(s2) + 1)))
		return (NULL);
	str[0] = '\0';
	str = ft_strcat(str, *s1);
	str = ft_strcat(str, s2);
	ft_strdel(s1);
	return (str);
}

char	*get_fd(int fd, t_gnl *tab)
{
	int i;

	i = 0;
	while (tab[i].fd != -2)
	{
		if (fd == tab[i].fd)
			return (tab[i].str);
		i++;
	}
	tab[i].fd = fd;
	tab[i].str = ft_strdup("");
	return (tab[i].str);
}

int		ft_ret(char **str, int ret, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(*str))
	{
		*line = NULL;
		return (0);
	}
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if (!(*line = ft_strsub(*str, 0, i)))
		return (-1);
	if (i == 0 && (*str)[i] != '\n')
		return (0);
	if ((*str)[i] == '\n')
	{
		tmp = ft_strdup(*str + i + 1);
		ft_strdel(str);
		*str = tmp;
	}
	else if (!(*str)[i] && ret == 0)
		ft_strdel(str);
	return (1);
}

void	ft_fillstr(t_gnl *tab, int fd, char *str)
{
	int i;

	i = 0;
	while (tab[i].fd != -2)
	{
		if (tab[i].fd == fd)
		{
			tab[i].str = str;
			break ;
		}
		i++;
	}
}

int		get_next_line(int fd, char **line)
{
	static t_gnl	tab[FDMAX];
	char			buf[BUFF_SIZE + 1];
	int				ret;
	int				i;
	char			*str;

	i = 0;
	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (tab[0].str == NULL)
		while (i < FDMAX)
			tab[i++].fd = -2;
	str = get_fd(fd, tab);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if ((str = ft_strjoinfree(&str, buf)) == NULL || ret == -1)
			return (-1);
		if (ft_strchr(str, '\n') != NULL)
			break ;
	}
	ret = ft_ret(&str, ret, line);
	ft_fillstr(tab, fd, str);
	return (ret);
}
