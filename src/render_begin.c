/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_begin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 17:18:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 08:07:11 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

t_float		create_float(float a, float b)
{
	t_float	x;

	x.x = a;
	x.y = b;
	return (x);
}

void		draw(t_mapf *mapf, int x, int y1, int y2, int color)
{
	int		y;

	y = 0;
	y1 = clamp(y1, 0, WIN_H - 1);
	y2 = clamp(y2, 0, WIN_H - 1);
	if (y2 == y1)
		mapf->sdl.pix[y1 * WIN_W + x] = color;
	else if (y2 > y1)
	{
		y = y1 + 1;
		mapf->sdl.pix[y1 * WIN_W + x] = 0x000000FF;
		while (y <= y2)
		{
			mapf->sdl.pix[y * WIN_W + x] = color;
			y++;
		}
	}
}

float		vector_measure(float x1, float y1, float x2, float y2)
{
	float dx;
	float dy;
	float res;

	dx = x2 - x1;
	dy = y2 - y1;
	res = sqrtf(dx * dx + dy * dy);
	return (res);
}

void		fill_pix(t_mapf *mapf)
{
	int		maxq = 32;
	t_queue	queue[maxq];
	t_queue	*head = queue;
	t_queue	*tail = queue;
	int		ytop[WIN_W];
	int		ybot[WIN_W];
	int		rendersect[mapf->nbsect];
	int		i = 0;

	while (i < WIN_W)
		ybot[i++] = WIN_H - 1;
	i = 0;
	while (i < WIN_W)
		ytop[i++] = 0;
	i = 0;
	while (i < mapf->nbsect)
		rendersect[i++] = 0;
	head->sect = mapf->player.sect;
	head->sx1 = 0;
	head->sx2 = WIN_W - 1;
	if (++head == queue + maxq)
		head = queue;
	while (head != tail)
	{
		t_queue	now = *tail;
		if (++tail == queue + maxq)
			tail = queue;
		if ((rendersect[now.sect] & 0x21))
			continue ;
		rendersect[now.sect]++;
		t_sector	*sect = &mapf->sectors[now.sect];
		int s = 0;
		while (s < sect->nbvert)
		{
			float vx1;
			float vy1;
			float vx2;
			float vy2;
			if (s == sect->nbvert - 1)
			{
				vx1 = sect->vert[s].x - mapf->player.where.x;
				vy1 = sect->vert[s].y - mapf->player.where.y;
				vx2 = sect->vert[0].x - mapf->player.where.x;
				vy2 = sect->vert[0].y - mapf->player.where.y;
			}
			else
			{
				vx1 = sect->vert[s].x - mapf->player.where.x;
				vy1 = sect->vert[s].y - mapf->player.where.y;
				vx2 = sect->vert[s + 1].x - mapf->player.where.x;
				vy2 = sect->vert[s + 1].y - mapf->player.where.y;
			}
			float pcos = mapf->player.anglecos;
			float psin = mapf->player.anglesin;
			float tx1 = vx1 * psin - vy1 * pcos;
			float tz1 = vx1 * pcos + vy1 * psin;
			float tx2 = vx2 * psin - vy2 * pcos;
			float tz2 = vx2 * pcos + vy2 * psin;
			if (tz1 <= 0 || tz2 <= 0)
			{
				float nearz = 0.0001f;
				float farz = 5.f;
				float nearside = 0.00001f;
				float farside = 20.f;
				t_float a = create_float(tx1, tz1);
				t_float b = create_float(tx2, tz2);
				t_float c = create_float(-nearside, nearz);
				t_float d = create_float(-farside, farz);
				t_float i1 = f_intersect(a, b, c, d);
				c = create_float(nearside, nearz);
				d = create_float(farside, farz);
				t_float i2 = f_intersect(a, b, c, d);
				if (tz1 < nearz)
				{
					if (i1.y > 0)
					{
						tx1 = i1.x;
						tz1 = i1.y;
					}
					else
					{
						tx1 = i2.x;
						tz1 = i2.y;
					}
				}
				if (tz2 < nearz)
				{
					if (i1.y > 0)
					{
						tx2 = i1.x;
						tz2 = i1.y;
					}
					else
					{
						tx2 = i2.x;
						tz2 = i2.y;
					}
				}
			}
			float xscale1 = HFOV / tz1;
			float yscale1 = VFOV / tz1;
			int x1 = (tx1 * xscale1) * -1 + WIN_W / 2;
			float xscale2 = HFOV / tz2;
			float yscale2 = VFOV / tz2;
			int x2 = WIN_W / 2 - (int)(tx2 * xscale2);
	//		if (x1 >= x2 || x2 < now.sx2 || x1 > now.sx1)
	//			break ;
			float yceil = sect->ceil - mapf->player.where.z;
			float yfloor = sect->floor - mapf->player.where.z;
			int neigh = sect->vert[s].neigh;
			float nyceil = 0;
			float nyfloor = 0;
			if (neigh >= 0)
			{
				nyceil = mapf->sectors[neigh].ceil - mapf->player.where.z;
				nyfloor = mapf->sectors[neigh].floor - mapf->player.where.z;
			}
# define Yaw(y, z) (y + z * mapf->player.yaw)
			int y1a = WIN_H / 2 - (int)(Yaw(yceil, tz1) * yscale1); 
			int y1b = WIN_H / 2 - (int)(Yaw(yfloor, tz1) * yscale1); 
			int y2a = WIN_H / 2 - (int)(Yaw(yceil, tz2) * yscale2); 
			int y2b = WIN_H / 2 - (int)(Yaw(yfloor, tz2) * yscale2); 
			int ny1a = WIN_H / 2 - (int)((nyceil + tz1 * mapf->player.yaw) * yscale1); 
			int ny1b = WIN_H / 2 - (int)((nyfloor + tz1 * mapf->player.yaw) * yscale1); 
			int ny2a = WIN_H / 2 - (int)((nyceil + tz2 * mapf->player.yaw) * yscale2); 
			int ny2b = WIN_H / 2 - (int)((nyfloor + tz2 * mapf->player.yaw) * yscale2);
			int beginx = max(x1, now.sx1);
			int	endx = min(x2, now.sx2);
			int x = beginx;
			while (x <= endx)
			{
				if (x2 - x1 == 0)
					break ;
				int ya = ((x - x1) * (y2a - y1a)) / (x2 - x1) + y1a;
				int yb = ((x - x1) * (y2b - y1b)) / (x2 - x1) + y1b;
				int cya = clamp(ya, ytop[x], ybot[x]);
				int cyb = clamp(yb, ytop[x], ybot[x]);
				draw(mapf, x, ytop[x], cya - 1, PURPLE);
				draw(mapf, x, cyb + 1, ybot[x], BROWN);
				if (neigh >= 0)
				{
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					int cnya = clamp(nya, ytop[x], ybot[x]);
					int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
					int cnyb = clamp(nyb, ytop[x], ybot[x]);
					//unsigned r1 = 0x010101 * (255 - z), r2 = 0x040003 * (31 - z /8);
					if (x == beginx || x == endx)
						draw(mapf, x, cya, cnya - 1, 0x000000FF);
					else
						draw(mapf, x, cya, cnya - 1, GREEN);
					ytop[x] = clamp(max(cya, cnya), ytop[x], WIN_H - 1);
					if (x == beginx || x == endx)
						draw(mapf, x, cnyb + 1, cyb, 0x000000FF);
					else
						draw(mapf, x, cnyb + 1, cyb, CYAN);
					ybot[x] = clamp(min(cyb, cnyb), 0, ybot[x]);
				}
				else
				{
					//unsigned r = 0x010101 * (255 - z);
					if (x == beginx || x == endx)
					draw(mapf, x, cya, cyb, 0x000000FF);
					else
					draw(mapf, x, cya, cyb, WF_COL);
				}
				x++;
			}
			if (neigh >= 0 && endx >= beginx && (head + maxq + 1 - tail) % maxq)
			{
				head->sect = neigh;
				head->sx1 = beginx;
				head->sx2 = endx;
				if (++head == queue + maxq)
					head = queue;
			}
			s++;
		}
		++rendersect[now.sect];
	}
}

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

void		slide_wall(t_mapf *mapf, int i)
{
	float		dx;
	float		dy;
	float		x;
	float		y;
	t_sector	*sec;
	t_float		proj;

	x = 0;
	y = 0;
	sec = &mapf->sectors[mapf->player.sect];
	if (i != sec->nbvert - 1)
	{
		dx = sec->vert[i + 1].x - sec->vert[i].x;
		dy = sec->vert[i + 1].y - sec->vert[i].y;
	}
	else
	{
		dx = sec->vert[0].x - sec->vert[i].x;
		dy = sec->vert[0].y - sec->vert[i].y;
	}
	if (dx == 0)
	{
		x = sec->vert[i].x;
		mapf->player.where.y += mapf->player.velo.y;
	}
	else if (dy == 0)
	{
		y = sec->vert[i].y;
		mapf->player.where.x += mapf->player.velo.x;
	}
	else
	{
		float	px = mapf->player.where.x;
		float	py = mapf->player.where.y;
		x = dy / dx;
		y = mapf->player.where.y - x * mapf->player.where.x;
		t_float		b;
		b = (t_float){mapf->player.where.x + 2, x *
			(mapf->player.where.x + 2) + y};
		proj.x = ((mapf->player.velo.x * (b.x - px) +
				mapf->player.velo.y * (b.y - py)) / vector_measure(px, py, b.x, b.y) *
				vector_measure(px, py, b.x, b.y) * (b.x - px));
		proj.y = ((mapf->player.velo.x * (b.x - px) +
				mapf->player.velo.y * (b.y - py)) / vector_measure(px, py, b.x, b.y) *
				vector_measure(px, py, b.x, b.y) * (b.y - py));
		mapf->player.where.x += proj.x;
		mapf->player.where.y += proj.y;
	}
}

int			check_port(t_mapf *mapf, int i, t_sector *sect)
{
	float	ps;
	float	ps2;
	float	px = mapf->player.where.x;
	float	py = mapf->player.where.y;
	float	dx = mapf->player.velo.x;
	float	dy = mapf->player.velo.y;

	if (i != sect->nbvert - 1)
	{
		ps = f_pointside((t_float){px, py}, (t_float){sect->vert[i].x, sect->vert[i].y},
			(t_float){sect->vert[i + 1].x, sect->vert[i + 1].y});
		ps2 = f_pointside((t_float){px + dx, py + dy}, (t_float){sect->vert[i].x, sect->vert[i].y},
			(t_float){sect->vert[i + 1].x, sect->vert[i + 1].y});
	}
	else
	{
		ps = f_pointside((t_float){px, py}, (t_float){sect->vert[i].x, sect->vert[i].y},
			(t_float){sect->vert[0].x, sect->vert[0].y});
		ps2 = f_pointside((t_float){px + dx, py + dy}, (t_float){sect->vert[i].x, sect->vert[i].y},
			(t_float){sect->vert[0].x, sect->vert[0].y});
	}
//	dprintf(1, "-----------------------------------------\n");
//	dprintf(1, "ps = %f\tps2 = %f\n", ps, ps2);
//	if (i != sect->nbvert - 1)
//		dprintf(1, "x1 = %d\ty1 = %d\tx2 = %d\ty2 = %d\n", sect->vert[i].x, sect->vert[i].y,
//				sect->vert[i + 1].x, sect->vert[i + 1].y);
//	else
//		dprintf(1, "x1 = %d\ty1 = %d\tx2 = %d\ty2 = %d\n", sect->vert[i].x, sect->vert[i].y,
//				sect->vert[0].x, sect->vert[0].y);
//	dprintf(1, "px =%f\tpy = %f\n", px, py);
//	dprintf(1, "dx =%f\tdy = %f\n", dx, dy);
	if ((ps >= fabs(dx * 4) && ps2 <= fabs(dx * 4)) || (ps <= fabs(dx * 4) && ps2 >= fabs(dx * 4)))
	{
		mapf->player.sect = sect->vert[i].neigh;
		return (1);
	}
	return (0);
}

int			check_horcoll(t_mapf *mapf)
{
	float	px = mapf->player.where.x;
	float	py = mapf->player.where.y;
	float	dx = mapf->player.velo.x;
	float	dy = mapf->player.velo.y;
	float	vmp;
	float	vmp2;
	float	vmw;
	int		i;
	t_sector	*sect;

	i = 0;
	sect = &mapf->sectors[mapf->player.sect];
	while (i < sect->nbvert)
	{
		if (i != sect->nbvert - 1)
		{
			vmw = vector_measure(sect->vert[i].x, sect->vert[i].y, sect->vert[i + 1].x, sect->vert[i + 1].y);
			vmp = vector_measure(sect->vert[i].x, sect->vert[i].y, px, py) +
				vector_measure(sect->vert[i + 1].x, sect->vert[i + 1].y, px, py);
			vmp2 = vector_measure(sect->vert[i].x, sect->vert[i].y, px + dx, py + dy ) +
				vector_measure(sect->vert[i + 1].x, sect->vert[i + 1].y, px + dx, py + dy);
		}
		else
		{
			vmw = vector_measure(sect->vert[i].x, sect->vert[i].y, sect->vert[0].x, sect->vert[0].y);
			vmp = vector_measure(sect->vert[i].x, sect->vert[i].y, px, py) +
				vector_measure(sect->vert[0].x, sect->vert[0].y, px, py);
			vmp2 = vector_measure(sect->vert[i].x, sect->vert[i].y, px + dx, py + dy ) +
				vector_measure(sect->vert[0].x, sect->vert[0].y, px + dx, py + dy);
		}
		if (vmp > vmp2 && vmp2 <= vmw + 0.2)
		{
			if (sect->vert[i].neigh != -1)
				check_port(mapf, i, sect);
			else
			{
					slide_wall(mapf, i);
					mapf->player.coll++;
					return (1);
			}
		}
		i++;
	}
	mapf->player.coll = 0;
	return (0);
}

void		move_chara(t_mapf *mapf, t_input *in)
{
	float	move_vec[2];
	float acc = 0.2f;
	float tmpx;
	float tmpy;

	move_vec[0] = 0.0f;
	move_vec[1] = 0.0f;
	if (in->key[SDL_SCANCODE_W])
	{
		move_vec[0] += mapf->player.anglecos*0.2f;
		move_vec[1] += mapf->player.anglesin*0.2f;
	}
	if (in->key[SDL_SCANCODE_S])
	{
		move_vec[0] -= mapf->player.anglecos*0.2f;
		move_vec[1] -= mapf->player.anglesin*0.2f;
	}
	if (in->key[SDL_SCANCODE_A])
	{
		move_vec[0] += mapf->player.anglesin*0.2f;
		move_vec[1] -= mapf->player.anglecos*0.2f;
	}
	if (in->key[SDL_SCANCODE_D])
	{
		move_vec[0] -= mapf->player.anglesin*0.2f;
		move_vec[1] += mapf->player.anglecos*0.2f;
	}
	tmpx = mapf->player.velo.x;
	tmpy = mapf->player.velo.y;
	mapf->player.velo.x = mapf->player.velo.x * (1 - acc) + move_vec[0]
	* acc;
	mapf->player.velo.y = mapf->player.velo.y * (1 - acc) + move_vec[1]
	* acc;
	if (check_horcoll(mapf) == 0)
	{
		mapf->player.where.x += mapf->player.velo.x;
		mapf->player.where.y += mapf->player.velo.y;
	}

}

void		render_check_event(t_mapf *mapf, t_input *in)
{
	move_chara(mapf, in);
	mouse_aim(mapf, in);
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

void		render(char *str)
{
	t_mapf	mapf;
	t_input	in;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&mapf, sizeof(t_mapf));
	if (!read_map(&mapf, str))
		return ;
	sdl_init(&mapf.sdl);
	SDL_WarpMouseInWindow(mapf.sdl.win, WIN_W / 2, WIN_H / 2);
	if ((SDL_SetRelativeMouseMode(SDL_ENABLE)) != 0)
		return ;
	mapf.player.velo.x = 0;
	mapf.player.velo.y = 0;
	mapf.player.velo.z = 0;
	mapf.player.yaw = 0;
	mapf.player.coll = 0;
	while (!in.quit)
	{
		in.xrel = 0;
		in.yrel = 0;
		mapf.player.where.z = mapf.sectors[mapf.player.sect].floor + EYE;
		clear_tab(&mapf.sdl);
		update_event(&in);
		render_check_event(&mapf, &in);
		fill_pix(&mapf);
		if (display_frame(mapf.sdl.ren, mapf.sdl.pix) == 0)
			return ;
		SDL_Delay(1000 / 60);
	}
}
