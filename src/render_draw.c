/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_draw.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 09:36:31 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 13:31:27 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

float		fvector_measure(float x1, float y1, float x2, float y2)
{
	float dx;
	float dy;
	float res;

	dx = x2 - x1;
	dy = y2 - y1;
	res = sqrtf(dx * dx + dy * dy);
	return (res);
}

t_float		create_float(float a, float b)
{
	t_float	x;

	x.x = a;
	x.y = b;
	return (x);
}

Uint32		add_light(Uint32 color)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;

	r = color >> 24;
	g = color >> 16;
	b = color >> 8;
	a = color;
	if (r * 1.8 < 255)
		r *= 1.8;
	else
		r = 255;
	if (g * 1.8 < 255)
		g *= 1.8;
	else
		g = 255;
	if (b * 1.8 < 255)
		b *= 1.8;
	else
		b = 255;
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

void		draw(t_mapf *mapf, int x, int y1, int y2, int color, t_sector *sect)
{
	int		y;

	y = 0;
	y1 = clamp(y1, 0, RWIN_H - 1);
	y2 = clamp(y2, 0, RWIN_H - 1);
	if (y2 == y1)
		mapf->sdl.pix[y1 * RWIN_W + x] = color;
	else if (y2 > y1)
	{
		y = y1 + 1;
		mapf->sdl.pix[y1 * RWIN_W + x] = 0x000000FF;
		while (y <= y2)
		{
			if (sect->lum == 1 )
				mapf->sdl.pix[y * RWIN_W + x] = add_light(color);
			else
				mapf->sdl.pix[y * RWIN_W + x] = color;
			y++;
		}
	}
}

void		draw_text(t_mapf *mapf, int ya, int yb, int x, int *ytop, int *ybot, int txtx, t_sector *sect, int s)
{
	Uint32	*p;
	int		y = clamp(ya, ytop[x], ybot[x]);
	int		cyb = clamp(yb, ytop[x], ybot[x]);
	float	tey;
	int		ty;
	int		ind = sect->vert[s].text - 1;

	SDL_LockSurface(mapf->wall[ind]);
	p = mapf->wall[ind]->pixels;
	while (y < cyb)
	{
		tey = (float)((float)y - (float)ya) / (float)((float)yb - (float)ya);
		ty = mapf->wall[ind]->h * tey;
		if (sect->lum == 1 )
			mapf->sdl.pix[y * RWIN_W + x] = add_light(p[txtx % 199 + ty * mapf->wall[ind]->w]);
		else
			mapf->sdl.pix[y * RWIN_W + x] = p[txtx % 199 + ty * mapf->wall[ind]->w];
		y++;
	}
}

void		fill_pix(t_mapf *mapf)
{
	int		maxq = 32;
	t_queue	queue[maxq];
	t_queue	*head = queue;
	t_queue	*tail = queue;
	int		ytop[RWIN_W];
	int		ybot[RWIN_W];
	int		rendersect[mapf->nbsect];
	int		i = 0;

	while (i < RWIN_W)
		ybot[i++] = RWIN_H - 1;
	i = 0;
	while (i < RWIN_W)
		ytop[i++] = 0;
	i = 0;
	while (i < mapf->nbsect)
		rendersect[i++] = 0;
	head->sect = mapf->player.sect;
	head->sx1 = 0;
	head->sx2 = RWIN_W - 1;
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
		mapf->rend_s[mapf->nbrend_s].id = now.sect;
		mapf->rend_s[mapf->nbrend_s].beginx = now.sx1;
		mapf->rend_s[mapf->nbrend_s].endx = now.sx2;
		mapf->nbrend_s++;
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
			int	u0 = 0;
			int u1 = 199;
			if (tz1 < 0 && tz2 < 0)
			{
				s++;
				continue ;
			}
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
				t_float org1 = (t_float){tx1, tz1};
				t_float org2 = (t_float){tx2, tz2};
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
				if (fabs(tx2 - tx1) > fabs(tz2 - tz1))
				{
					u0 = (tx1 - org1.x) * 199 / (org2.x - org1.x);
					u1 = (tx2 - org1.x) * 199 / (org2.x - org1.x);
				}
				else
				{
					u0 = (tz1 - org1.y) * 199 / (org2.y - org1.y);
					u1 = (tz2 - org1.y) * 199 / (org2.y - org1.y);
				}
			}
			float xscale1 = HFOV / tz1;
			float yscale1 = VFOV / tz1;
			int x1 = (tx1 * xscale1) * -1 + RWIN_W / 2;
			float xscale2 = HFOV / tz2;
			float yscale2 = VFOV / tz2;
			int x2 = RWIN_W / 2 - (int)(tx2 * xscale2);
			if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2)
			{
				s++;
				continue ;
			}
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
			int y1a = RWIN_H / 2 - (int)(YAW(yceil, tz1, mapf->player.yaw) * yscale1); 
			int y1b = RWIN_H / 2 - (int)(YAW(yfloor, tz1, mapf->player.yaw) * yscale1); 
			int y2a = RWIN_H / 2 - (int)(YAW(yceil, tz2, mapf->player.yaw) * yscale2); 
			int y2b = RWIN_H / 2 - (int)(YAW(yfloor, tz2, mapf->player.yaw) * yscale2); 
			int ny1a = RWIN_H / 2 - (int)((nyceil + tz1 * mapf->player.yaw) * yscale1);
			int ny1b = RWIN_H / 2 - (int)((nyfloor + tz1 * mapf->player.yaw) * yscale1);
			int ny2a = RWIN_H / 2 - (int)((nyceil + tz2 * mapf->player.yaw) * yscale2);
			int ny2b = RWIN_H / 2 - (int)((nyfloor + tz2 * mapf->player.yaw) * yscale2);
			int beginx = max(x1, now.sx1);
			int	endx = min(x2, now.sx2);
			int x = beginx;
			while (x <= endx)
			{
				if (x2 - x1 == 0)
					break ;
				int	txtx = ((u0 * (x2 - x) * tz2) + (u1 * (x - x1) * tz1)) / ((x2 - x) * tz2 + (x - x1) * tz1);
				int ya = ((x - x1) * (y2a - y1a)) / (x2 - x1) + y1a;
				int yb = ((x - x1) * (y2b - y1b)) / (x2 - x1) + y1b;
				int cya = clamp(ya, ytop[x], ybot[x]);
				int cyb = clamp(yb, ytop[x], ybot[x]);
				draw(mapf, x, ytop[x], cya - 1, DARK_GREY, sect);
				draw(mapf, x, cyb + 1, ybot[x], BROWN, sect);
				if (neigh >= 0)
				{
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					int cnya = clamp(nya, ytop[x], ybot[x]);
					int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
					int cnyb = clamp(nyb, ytop[x], ybot[x]);
					//unsigned r1 = 0x010101 * (255 - z), r2 = 0x040003 * (31 - z /8);
					if (x == beginx || x == endx)
						draw(mapf, x, cya, cnya - 1, 0x000000FF, sect);
					else
						draw_text(mapf, ya, nya - 1, x, ytop, ybot, txtx, sect, s);
					ytop[x] = clamp(max(cya, cnya), ytop[x], RWIN_H - 1);
					if (x == beginx || x == endx)
						draw(mapf, x, cnyb + 1, cyb, 0x000000FF, sect);
					else
						draw_text(mapf, nyb + 1, yb, x, ytop, ybot, txtx, sect, s);
					ybot[x] = clamp(min(cyb, cnyb), 0, ybot[x]);
				}
				else
				{
					//unsigned r = 0x010101 * (255 - z);
					if (x == beginx || x == endx)
					draw(mapf, x, cya, cyb, 0x000000FF, sect);
					else
					{
				//	dprintf(1, "cya = %d cyab = %d\n", cya, cyb);
					draw_text(mapf, ya, yb, x, ytop, ybot, txtx, sect, s);
				//	draw(mapf, x, cya, cyb, WF_COL);
					}
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
