/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <jfeve@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:08:32 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 17:22:39 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

int				usage(void)
{
	ft_putendl("Usage : ./doom-nukem <file>\n\tor ./doom-nukem edit.");
	return (0);
}

int				init_edit(t_edit *edit)
{
	if (sdl_init(&edit->sdl) == 0)
		return (0);
	edit->err = 0;
	return (1);
}

void			set_grid(t_edit *edit)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y % 10 == 0 || x % 10 == 0)
				edit->sdl.pix[y * WIN_W + x] = 0x00A200FF;
			x++;
		}
		y++;
	}
}

void			draw_vert(t_lis *tmp, t_edit *edit)
{
	int x;
	int y;

	x = tmp->x - 4;
	y = tmp->y - 4;
	while (x <= tmp->x + 4)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[(y + 8) * WIN_W + x] = WHITE;
		x++;
	}
	while (y <= tmp->y + 4)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[y * WIN_W + (x - 9)] = WHITE;
		y++;
	}
	edit->sdl.pix[tmp->y * WIN_W + tmp->x] = WHITE;
}

void			put_vert(t_lis *vert, t_edit *edit)
{
	t_lis		*tmp;

	tmp = vert;
	while (tmp != NULL)
	{
		draw_vert(tmp, edit);
		tmp = tmp->next;
	}
}

void			bresen(t_lis a, t_lis b, t_sdl *sdl)
{
	int dx;
	int dy;
	int e;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (dx > 0)
	{
		if (dy < 0)
		{
			if (dx >= -1 * dy)
			{
				e = dx;
				dx *= 2;
				dy *= 2;
				while (a.x != b.x)
				{
					sdl->pix[a.y * WIN_W + a.x] = WHITE;
					e += dy;
					if (e < 0)
					{
						a.y -=1;
						e += dx;
					}
					a.x +=1;
				}
			}
			else
			{
				e = dy;
				dx *= 2;
				dy *= 2;
				while (a.y != b.y)
				{
					sdl->pix[a.y * WIN_W + a.x] = WHITE;
					e += dx;
					if (e > 0)
					{
						a.x +=1;
						e += dy;
					}
					a.y -=1;
				}
			}
		}
		else if (dy > 0)
		{
			if (dx >= dy)
			{
				e = dx;
				dx *= 2;
				dy *= 2;
				while (a.x != b.x)
				{
					sdl->pix[a.y * WIN_W + a.x] = WHITE;
					e -= dy;
					if (e < 0)
					{
						a.y +=1;
						e += dx;
					}
					a.x +=1;
				}
			}
			else
			{
				e = dy;
				dx *= 2;
				dy *= 2;
				while (a.y != b.y)
				{
					sdl->pix[a.y * WIN_W + a.x] = WHITE;
					e -= dx;
					if (e < 0)
					{
						a.x +=1;
						e += dy;
					}
					a.y +=1;
				}
			}
		}
		else
		{
			while (a.x != b.x)
			{
				sdl->pix[a.y * WIN_W + a.x] = WHITE;
				a.x++;
			}
		}
	}
	else if (dx == 0)
	{
		if (dy > 0)
		{
			while (a.y != b.y)
			{
				sdl->pix[a.y * WIN_W + a.x] = WHITE;
				a.y++;
			}
		}
		else
		{
			while (a.y != b.y)
			{
				sdl->pix[a.y * WIN_W + a.x] = WHITE;
				a.y--;
			}
		}
	}
	else
		bresen(b, a, sdl);
}

void			hud(t_edit *edit)
{
	int x;
	int y;

	x = 0;
	y = 851;
	while (y < 860)
	{
		x = 0;
		while (x < WIN_W)
		{
			edit->sdl.pix[y * WIN_W + x] = 0x000000FF;
			x++;
		}
		y++;
	}
	x = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			edit->sdl.pix[y * WIN_W + x] = 0x656565FF;
			x++;
		}
		y++;
	}
	x = 250;
	y = 920;
	edit->sdl.pix[(y + 10) * WIN_W + x + 10] = WHITE;
	while (x < 270)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[(y + 20) * WIN_W + x] = WHITE;
		x++;
	}
	y = 920;
	while (y < 940)
	{
		edit->sdl.pix[y * WIN_W + x] = WHITE;
		edit->sdl.pix[y * WIN_W + x - 20] = WHITE;
		y++;
	}
}

void			level_editor(void)
{
	t_lis		*vert;
	t_edit		edit;
	t_input		in;

	ft_bzero(&in, sizeof(t_input));
	ft_bzero(&edit, sizeof(t_edit));
	vert = NULL;
	if (init_edit(&edit) == 0)
		return (ft_putendl("Init Edit Error"));
	while (!in.quit)
	{
		update_event(&in);
		check_event(&in, &vert);
		set_grid(&edit);
		put_vert(vert, &edit);
		hud(&edit);
		t_lis *tmp;

		tmp = vert;
		while (tmp != NULL)
		{
			if (tmp->next)
			{
				bresen(*tmp, *tmp->next, &edit.sdl);
			}
			//if (tmp->next == NULL)
//			{
//				t_lis point;
//
//				point.x = in.x;
//				point.y = in.y;
//				bresen(*tmp, point, &edit.sdl);
//			}
			tmp = tmp->next;
		}
		if (display_frame(edit.sdl.ren, edit.sdl.pix) == 0)
		{
			free_sdl(&edit.sdl, 5);
			return ;
		}
		SDL_Delay(1000/60);
	}
	return ;
}

int				main(int argc, char **argv)
{
	if (argc != 2)
		return(usage());
	if (strcmp(argv[1], "edit") == 0)
		level_editor();
}
