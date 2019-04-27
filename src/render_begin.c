/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_begin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 17:18:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 20:26:05 by jfeve       ###    #+. /#+    ###.fr     */
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
//			if (tz1 <= 0 && tz2 <= 0)
//				continue ;
			if (tz1 <= 0 || tz2 < 0)
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
			int x1 = (tx1 * xscale1);
			x1 = x1 * -1 + WIN_W / 2;
			float xscale2 = HFOV / tz2;
			float yscale2 = VFOV / tz2;
			int x2 = WIN_W / 2 - (int)(tx2 * xscale2);
//			if (x1 >= x2 || x2 < now.sx2 || x1 > now.sx1)
//				continue ;
			float yceil = sect->ceil - mapf->player.where.z;
			float yfloor = sect->floor - mapf->player.where.z;
			int neigh = sect->vert[s].neigh;
			float nyceil = 0;
			float nyfloor = 0;
			if (neigh >= 0)
			{
				nyceil = sect[neigh].ceil - mapf->player.where.z;
				nyfloor = sect[neigh].floor - mapf->player.where.z;
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

	mapf->player.angle += in->xrel * 0.03f;
	mapf->player.anglesin = sin(mapf->player.angle);
	mapf->player.anglecos = cos(mapf->player.angle);
	yaw = f_clamp(yaw - in->yrel * 0.05f, -5, 5);
	mapf->player.yaw -= yaw - mapf->player.velo.z * 0.5f;
	mapf->player.yaw = f_clamp(mapf->player.yaw, -5, 4);
}

void		move_chara(t_mapf *mapf, t_input *in)
{
	float	move_vec[2];
	float acc = 0.2f;

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
	mapf->player.velo.x = mapf->player.velo.x * (1 - acc) + move_vec[0]
	* acc;
	mapf->player.velo.y = mapf->player.velo.y * (1 - acc) + move_vec[1]
	* acc;
	mapf->player.where.x += mapf->player.velo.x;
	mapf->player.where.y += mapf->player.velo.y;
}

void		render_check_event(t_mapf *mapf, t_input *in)
{
	move_chara(mapf, in);
	mouse_aim(mapf, in);
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
}

void		render(char *str)
{
	t_mapf	mapf;
	t_input	in;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&mapf, sizeof(t_mapf));
	read_map(&mapf, str);
	sdl_init(&mapf.sdl);
	SDL_WarpMouseInWindow(mapf.sdl.win, WIN_W / 2, WIN_H / 2);
	if ((SDL_SetRelativeMouseMode(SDL_ENABLE)) != 0)
		return ;
	mapf.player.where.x = mapf.pl_x;
	mapf.player.where.y = mapf.pl_y;
	mapf.player.sect = mapf.pl_sec;
	mapf.player.where.z = mapf.sectors[mapf.pl_sec].floor + EYE;
	mapf.player.velo.x = 0;
	mapf.player.velo.y = 0;
	mapf.player.velo.z = 0;
	mapf.player.angle = 0;
	mapf.player.anglecos = cos(0);
	mapf.player.anglesin = sin(0);
	mapf.player.yaw = 0;
	while (!in.quit)
	{
		in.xrel = 0;
		in.yrel = 0;
		clear_tab(&mapf.sdl);
		update_event(&in);
		render_check_event(&mapf, &in);
		fill_pix(&mapf);
		if (display_frame(mapf.sdl.ren, mapf.sdl.pix) == 0)
			return ;
		SDL_Delay(1000 / 60);
	}
}
