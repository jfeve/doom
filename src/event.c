/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:16:42 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:34:26 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			update_event(t_input *in)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			in->quit = SDL_TRUE;
		else if (event.type == SDL_KEYDOWN)
			in->key[event.key.keysym.scancode] = SDL_TRUE;
		else if (event.type == SDL_KEYUP)
			in->key[event.key.keysym.scancode] = SDL_FALSE;
		else if (event.type == SDL_MOUSEMOTION)
		{
			in->x = event.motion.x;
			in->y = event.motion.y;
			in->xrel = event.motion.xrel;
			in->yrel = event.motion.yrel;
		}
		else if (event.type == SDL_MOUSEWHEEL)
		{
			in->xwheel = event.wheel.x;
			in->ywheel = event.wheel.y;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			in->mouse[event.button.button] = SDL_TRUE;
		else if (event.type == SDL_MOUSEBUTTONUP)
			in->mouse[event.button.button] = SDL_FALSE;
	}
}

t_lis			*create_vert(int x, int y)
{
	t_lis		*vert;

	if (!(vert = (t_lis*)malloc(sizeof(t_lis))))
		return (NULL);
	vert->x = x;
	vert->y = y;
	vert->next = NULL;
	return (vert);
}

int				parse_data(int x, int y, t_lis **vert)
{
	t_lis		*tmp;

	tmp = *vert;
	while(tmp != NULL)
	{
		if (tmp->x == x && tmp->y == y)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void			add_vert(int x, int y, t_lis **vert)
{
	t_lis		*point;
	t_lis		*tmp;

	if (parse_data(x, y, vert) == 0)
	{
		dprintf(1, "already set !\n");
		return ;
	}
	if (!(point = (t_lis*)malloc(sizeof(t_lis))))
		return ;
	point->x = x;
	point->y = y;
	point->next = NULL;
	tmp = *vert;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = point;
}

void			check_event(t_input *in, t_lis **vert)
{
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	if (in->mouse[SDL_BUTTON_LEFT])
	{
		if (*vert == NULL)
			*vert = create_vert(in->x, in->y);
		else
			add_vert(in->x, in->y, vert);
		print_lis(vert);
		in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
	}
}
