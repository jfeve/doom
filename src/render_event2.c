/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_event2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 15:16:52 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 15:29:24 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	jump_norm(t_mapf *mapf)
{
	if (mapf->player.where.z - mapf->player.eye
	> (float)mapf->sectors[mapf->player.sect].floor)
		mapf->player.add_z -= 0.5;
	else if (mapf->player.add_z >= 4 && mapf->player.add_z < 5)
		mapf->player.add_z -= 0.25;
	else
	{
		mapf->player.add_z = 0;
		mapf->player.state = moving;
	}
}

void		jump(t_mapf *mapf, t_input *in)
{
	if (in->key[SDL_SCANCODE_SPACE] && (mapf->player.state != flying
	&& mapf->player.state != jumping && mapf->player.state != falling))
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
			mapf->player.state = falling;
	}
	else if (mapf->player.state == falling)
		jump_norm(mapf);
}

void		mouse_aim(t_mapf *mapf, t_input *in)
{
	float yaw;

	yaw = 0;
	mapf->player.angle += in->xrel * 0.02f;
	mapf->player.anglesin = sin(mapf->player.angle);
	mapf->player.anglecos = cos(mapf->player.angle);
	yaw = f_clamp(yaw - in->yrel * 0.02f, -5, 5);
	mapf->player.yaw -= yaw - mapf->player.velo.z * 0.5f;
	mapf->player.yaw = f_clamp(mapf->player.yaw, -4, 3);
}
