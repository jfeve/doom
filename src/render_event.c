/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_event.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 09:35:16 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 21:57:39 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	fly(t_mapf *mapf, t_input *in)
{
	if (in->key[SDL_SCANCODE_F])
	{
		if (mapf->player.state == flying)
		{
			mapf->player.add_z = mapf->player.where.z - mapf->player.eye
			- mapf->sectors[mapf->player.sect].floor;
			mapf->player.state = falling;
		}
		else
			mapf->player.state = flying;
		in->key[SDL_SCANCODE_F] = SDL_FALSE;
	}
	if (mapf->player.state == flying)
	{
		if (in->key[SDL_SCANCODE_SPACE] && mapf->player.where.z + 0.3
		< mapf->sectors[mapf->player.sect].ceil)
			mapf->player.add_z += 0.3;
		if (in->key[SDL_SCANCODE_LCTRL] && mapf->player.where.z - 0.3
		> mapf->sectors[mapf->player.sect].floor + EYE)
			mapf->player.add_z -= 0.3;
	}
}

static void	crouch(t_mapf *mapf, t_input *in)
{
	if (in->key[SDL_SCANCODE_LCTRL] && mapf->player.state != flying)
	{
		in->key[SDL_SCANCODE_LCTRL] = SDL_FALSE;
		if (mapf->player.state == crouching)
			mapf->player.state = moving;
		else if (mapf->player.state == nmoving || mapf->player.state == moving
		|| mapf->player.state == running)
			mapf->player.state = crouching;
	}
	if (mapf->player.state == crouching)
	{
		if (mapf->player.eye >= (int)DUCK)
			mapf->player.eye -= 1;
	}
	else if (mapf->player.state != crouching && mapf->player.eye < (int)EYE)
	{
		mapf->player.eye += 1;
		if (mapf->player.eye >= (int)EYE)
			mapf->player.where.z = mapf->sectors[mapf->player.jump_sec].floor
			+ mapf->player.eye + mapf->player.add_z;
	}
}

static void	plrunning(t_mapf *mapf, t_input *in)
{
	if (in->key[SDL_SCANCODE_LSHIFT])
	{
		in->key[SDL_SCANCODE_LSHIFT] = SDL_FALSE;
		if (mapf->player.state == running)
		{
			mapf->player.state = moving;
			mapf->coeff = 1;
		}
		else if (mapf->player.state != crouching)
			mapf->player.state = running;
	}
	if (mapf->player.state == running)
	{
		mapf->coeff = 2;
	}
}

static int	click(t_mapf *mapf, t_hud *hud)
{
	char	*tmp;

	hud->anim = SDL_TRUE;
	if (hud->id == 0 && mapf->player.ammo > 0)
	{
		mapf->player.ammo--;
		SDL_FreeSurface(hud->nbammo);
		if (!(tmp = ft_itoa(mapf->player.ammo)))
			return (0);
		if (!(hud->nbammo = init_text(hud->arial, tmp, mapf->sdl.form->format,
		SDL_BLACK)))
		{
			ft_strdel(&tmp);
			return (0);
		}
		Mix_PlayChannel(1, hud->gunshot, 0);
		ft_strdel(&tmp);
	}
	else if (hud->id == 6)
		Mix_PlayChannel(1, hud->empty, 0);
	return (1);
}

int			render_check_event(t_mapf *mapf, t_input *in, t_hud *hud)
{
	move_chara(mapf, in);
	if (!pick_items(mapf, hud))
		return (0);
	mouse_aim(mapf, in);
	jump(mapf, in);
	fly(mapf, in);
	plrunning(mapf, in);
	crouch(mapf, in);
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	if (in->key[SDL_SCANCODE_J])
	{
	}
	if (in->mouse[SDL_BUTTON_LEFT])
		if (!click(mapf, hud))
			return (0);
	return (1);
}
