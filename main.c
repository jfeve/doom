/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 04:45:53 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 12:45:37 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		main(int argc, char **argv)
{
	pid_t child;
		pid_t waiting;
	char	*new_arg[] = {argv[1], NULL};

	child = fork();
	if (child == 0)
	{
		dprintf(1, "test  %ld\n", (long)child);
		execve(argv[1], new_arg, NULL);
		exit(0);
	}
	else
	{
		int status;
		while ((waiting = wait(&status)) != child) ;
		dprintf(1, "%d done\n", waiting);
	}
	dprintf(1, "test  %ld  %ld\n", (long)child, (long)waiting);
	return (0);
}
