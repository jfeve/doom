/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 04:45:53 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 05:25:58 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		main(int argc, char **argv)
{
//	pid_t pid;

//	pid = fork();
//	if (pid == -1)
//		ft_putendl("error");
//	else if (pid == 0)
//	{		
//	}
	char	*new_arg[] = {argv[1], NULL};

	(void)argc;
	if (execve(argv[1], new_arg, NULL) != 1)
		dprintf(1, "done\n");
	return (0);
}
