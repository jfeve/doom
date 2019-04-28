/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_event.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 09:35:16 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 12:13:37 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

void		mouse_aim(t_mapf *mapf, t_input *in)
{
	float yaw = 0;

	mapf->player.angle += in->xrel * 0.02f;
	mapf->player.anglesin = sin(mapf->player.angle);
	mapf->player.anglecos = cos(mapf->player.angle);
	yaw = f_clamp(yaw - in->yrel * 0.04f, -5, 5);
	mapf->player.yaw -= yaw - mapf->player.velo.z * 0.5f;
	mapf->player.yaw = f_clamp(mapf->player.yaw, -4, 3);
}

void		jump(t_mapf *mapf, t_input *in)
{
	if (in->key[SDL_SCANCODE_SPACE] && (mapf->player.state != flying && mapf->player.state != jumping && mapf->player.state != falling))
	{
		mapf->player.state = jumping;
		mapf->player.jump_sec = mapf->player.sect;
		in->key[SDL_SCANCODE_SPACE] = SDL_FALSE;
	}
	if (mapf->player.state == jumping)
	{
		if (mapf->player.add_z < 4)
			mapf->player.add_z += 0.5;
		else if (mapf->player.add_z >= 4 && mapf->player.add_z < 5)
			mapf->player.add_z += 0.25;
		else
		{
			mapf->player.state = falling;
		}
	}
	else if (mapf->player.state == falling)
	{
		if (mapf->player.where.z > mapf->sectors[mapf->player.sect].floor + EYE)
			mapf->player.add_z -= 0.5;
		else if (mapf->player.add_z >= 4 && mapf->player.add_z < 5)
			mapf->player.add_z -= 0.25;
		else
		{
			mapf->player.state = nmoving;
		}
	}
}

void		fly(t_mapf *mapf, t_input *in)
{
	if (in->key[SDL_SCANCODE_F])
	{
		if (mapf->player.state == flying)
			mapf->player.state = falling;
		else
			mapf->player.state = flying;
		in->key[SDL_SCANCODE_F] = SDL_FALSE;
	}
	if (mapf->player.state == flying)
	{
		if (in->key[SDL_SCANCODE_SPACE])
		{
			if (mapf->player.where.z + 0.3 < mapf->sectors[mapf->player.sect].ceil)
				mapf->player.add_z += 0.3;
		}
		if (in->key[SDL_SCANCODE_LCTRL])
		{
			if (mapf->player.where.z - 0.3 > mapf->sectors[mapf->player.sect].floor + EYE)
				mapf->player.add_z -= 0.3;
		}
	}
}

void		crouch(t_mapf *mapf, t_input *in)
{
	if (in->key[SDL_SCANCODE_LCTRL] && mapf->player.state != flying)
	{
		in->key[SDL_SCANCODE_LCTRL] = SDL_FALSE;
		if (mapf->player.state == crouching)
			mapf->player.state = nmoving;
		else if (mapf->player.state == nmoving || mapf->player.state == moving)
			mapf->player.state = crouching;
	}
	if (mapf->player.state == crouching)
	{
		if (mapf->player.eye >= (int)DUCK)
			mapf->player.eye -= 1;
	}
	else if (mapf->player.state != crouching && mapf->player.eye <= (int)EYE)
	{
		mapf->player.eye += 1;
	}
}

void		render_check_event(t_mapf *mapf, t_input *in)
{
	move_chara(mapf, in);
	mouse_aim(mapf, in);
	jump(mapf, in);
	fly(mapf, in);
	crouch(mapf, in);
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	if (in->key[SDL_SCANCODE_H])
	{
		if (mapf->player.sect == mapf->nbsect - 1)
			mapf->player.sect = 0;
		else
			mapf->player.sect++;
		in->key[SDL_SCANCODE_H] = SDL_FALSE;
	}
	if (in->key[SDL_SCANCODE_J])
	{
		if (mapf->player.sect == 0)
			mapf->player.sect = mapf->nbsect - 1;
		else
			mapf->player.sect--;
		in->key[SDL_SCANCODE_J] = SDL_FALSE;
	}
}
