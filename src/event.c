/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 19:16:42 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 19:25:31 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void			update_event(t_input *in)
{
	while (SDL_PollEvent(&in->event))
	{
		if (in->event.type == SDL_QUIT)
			in->quit = SDL_TRUE;
		else if (in->event.type == SDL_KEYDOWN)
			in->key[in->event.key.keysym.scancode] = SDL_TRUE;
		else if (in->event.type == SDL_KEYUP)
			in->key[in->event.key.keysym.scancode] = SDL_FALSE;
		else if (in->event.type == SDL_MOUSEMOTION)
		{
			in->x = in->event.motion.x;
			in->y = in->event.motion.y;
			in->xrel = in->event.motion.xrel;
			in->yrel = in->event.motion.yrel;
		}
		else if (in->event.type == SDL_MOUSEWHEEL)
		{
			in->xwheel = in->event.wheel.x;
			in->ywheel = in->event.wheel.y;
		}
		else if (in->event.type == SDL_MOUSEBUTTONDOWN)
			in->mouse[in->event.button.button] = SDL_TRUE;
		else if (in->event.type == SDL_MOUSEBUTTONUP)
			in->mouse[in->event.button.button] = SDL_FALSE;
	}
}

void			cancel_last(t_edit*edit)
{
	t_lis		*tmp;
	
	if (edit->vert == NULL)
		return ;
	tmp = edit->vert;
	if (tmp->next)
		while(tmp->next->next)
			tmp = tmp->next;
	if (tmp->next)
	{
		free(tmp->next);
		tmp->next = NULL;
	}
	else
	{
		free(edit->vert);
		edit->vert = NULL;
	}
}

/*
 *int				vec_here(t_lis *tmp, t_lis *vert, t_input *in)
 *{
 *    float		m;
 *    float		p;
 *
 *    //y = mx + p;
 *    m = ((float)tmp->y - (float)tmp->next->y) / ((float)tmp->y - (float)tmp->next->y);
 *    p = (float)tmp->y - m * (float)tmp->x;
 *
 *    return (0);
 *}
 */

/*
 *int				check_on_vec(t_edit *edit, t_input *in)
 *{
 *    t_lis		*tmp;
 *    t_sec		*sec;
 *
 *    if (edit->sect == NULL)
 *        return (0);
 *    sec = edit->sect;
 *    while (sec)
 *    {
 *        tmp = sec->vert;
 *        while (tmp->next)
 *        {
 *            if (vec_here(tmp, tmp->next, in) == 1)
 *                return (1);
 *            tmp = tmp->next;
 *        }
 *        sec = sec->next;
 *    }
 *    return (0);
 *}
 */

void			check_event(t_input *in, t_edit *edit)
{
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	if (in->key[SDL_SCANCODE_R])
	{
		edit->vert = NULL;
		edit->sect = NULL;
	}
	if (in->key[SDL_SCANCODE_Z])
	{
		cancel_last(edit);
		in->key[SDL_SCANCODE_Z] = SDL_FALSE;
	}
	/*
	 *if (in->mouse[SDL_BUTTON_RIGHT])
	 *{
	 *    if (check_on_vec(edit, in) == 1)
	 *    {
	 *        dprintf(1, "suce\n");
	 *        get_portal_coord();
	 *        get_neighbor();
	 *    }
	 *}
	 */
	if (in->mouse[SDL_BUTTON_LEFT] && in->y <= 850)
	{
		if (edit->vert == NULL)
			edit->vert = create_vert(in->x, in->y);
		else
			add_vert(in->x, in->y, edit);
		in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
	}
}
