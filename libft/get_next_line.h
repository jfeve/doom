/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:23:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 00:51:49 by nzenzela    ###    #+. /#+    ###.fr     */
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
# ifdef HAVE_SYS_UIO_H
#  include <sys/uio.h>
# endif
typedef struct	s_gnl
{
	char		*str;
	int			fd;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
