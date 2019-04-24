/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_begin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 17:18:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 21:48:16 by jfeve       ###    #+. /#+    ###.fr     */
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

void		fill_pix(t_mapf *mapf, t_input *in)
{
	int		maxq = 32;
	t_queue	queue[maxq];
	t_queue	*head = queue;
	t_queue	*tail = queue;
	int		ytop[WIN_W];
	int		ybot[WIN_W];
	int		rendersect[nbsect];
	int		i = 0;

	while (i < WIN_W)
		ybot[i++] = WIN_H - 1;
	i = 0;
	while (i < nbsect)
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
		if (!(rendersect[now.sect] & 0x21))
			break ;
		rendersect[now.sect]++;
		t_sector	*sect = &mapf->sector[now.sect];
		int s = 0;
		while (s < setc->nbvert)
		{
			float vx1 = sect->vert[s].x - player.where.x;
			float vy1 = sect->vert[s].y - player.where.y;
			float vx2 = sect->vert[s + 1].x - player.where.x;
			float vy2 = sect->vert[s + 1].y - player.where.y;
			float pcos = player.anglecos;
			float psin = player.anglesin;
			float tx1 = vx1 * psin - vy1 * pcos;
			float tz1 = vx1 * pcos + vy1 * psin;
			float tx2 = vx2 * psin - vy2 * pcos;
			float tz2 = vx2 * pcos + vy2 * psin;
			if (tz1 <= 0 || tz2 < 0)
			{
				float nearz = 1e-4f;
				float farz = 5;
				float nearside = 1e-5f;
				float farside = 20.0f;
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
			float xscale1 = hfov / tz1;
			float yscale1 = vfov / tz1;
			int x1 = WIN_W / 2 - (int)(tx1 * xscale1);
			float xscale2 = hfov / tz2;
			float yscale2 = vfov / tz2;
			int x2 = WIN_W / 2 - (int)(tx2 * xscale2);
			if (!(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2))
				return ;
			float yceil = sect->ceil - player.where.z;
			float yfloor = sect->floor - player.where.z;
			int neigh = sect->neigh[s];
			if (neigh >= 0)
			{
				float nyceil = sect[neigh].ceil - player.where.z;
				float nyfloor = sect[neigh].floor - player.where.z;
			}
			//define Yaw(y, z) (y + z * player.yaw)
			int y1a = WIN_H / 2 - (int)((yceil + tz1 * player.yaw) * yscale1); 
			int y1b = WIN_H / 2 - (int)((yfloor + tz1 * player.yaw) * yscale1); 
			int y2a = WIN_H / 2 - (int)((yceil + tz2 * player.yaw) * yscale2); 
			int y2b = WIN_H / 2 - (int)((yfloor + tz2 * player.yaw) * yscale2); 
			int ny1a = WIN_H / 2 - (int)((nyceil + tz1 * player.yaw) * yscale1); 
			int ny1b = WIN_H / 2 - (int)((nyfloor + tz1 * player.yaw) * yscale1); 
			int ny2a = WIN_H / 2 - (int)((nyceil + tz2 * player.yaw) * yscale2); 
			int ny2b = WIN_H / 2 - (int)((nyfloor + tz2 * player.yaw) * yscale2);
			int beginx = max(x1, now.sx1);
			int	endx = min(x2, now.sx2);
			int x = beginx;
			while (x <= endx)
			{
				int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
				int cya = clamp(ya, ytop[x], ybottom[x]);
				int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
				int cyb = clamp(yb, ytop[x], ybottom[x]);
				draw(x, ytop[x], cya - 1);
				draw(x, cyb + 1, ybottom[x]);
				if (neigh >= 0)
				{
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					int cnya = clamp(nya, ytop[x], ybottom[x]);
					int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
					int cnyb = clamp(nyb, ytop[x], ybottom[x]);
					//unsigned r1 = 0x010101 * (255 - z), r2 = 0x040003 * (31 - z /8);
					draw(x, cya, cnya - 1);
					ytop[x] = clamp(max(cya, cnya), ytop[x], WIN_H - 1);
					draw(x, cnyb + 1, cyb);
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]);
				}
				else
				{
					//unsigned r = 0x010101 * (255 - z);
					draw(x, cya, cyb);
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

void		render(char *str)
{
	t_mapf	mapf;
	t_input	in;

	ft_bzero(&in, sizeof(t_input));
//	mapf = load_data(str);
	while (!in.quit)
	{
		fill_pix(/*&mapf, */&in);
		if (display_frame(mapf.sdl.ren, mapf.sdl.pix) == 0)
			return ;
		SDL_Delay(1000 / 60);
	}
}
