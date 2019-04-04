/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:23:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/18 15:35:01 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 128
# define FDMAX 126
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/uio.h>

typedef struct	s_gnl
{
	char		*str;
	int			fd;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
