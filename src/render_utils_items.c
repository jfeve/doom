/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_utils_items.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 13:13:42 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 15:11:00 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Swaps 2 objects
*/

static void	objs_swap(t_sprite *a, t_sprite *b)
{
	t_sprite	c;

	c = (t_sprite){a->x, a->y, a->type, a->tx, a->tz, a->is_enemy};
	*a = (t_sprite){b->x, b->y, b->type, b->tx, b->tz, b->is_enemy};
	*b = (t_sprite){c.x, c.y, c.type, c.tx, c.tz, c.is_enemy};
}

/*
** Bubble-sort object from nearest to farthest
*/

void		bubble_sort(t_sprite arr[], int n, t_point player)
{
	int		i;
	int		j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (vector_measure(arr[j].x, arr[j].y, player.x, player.y) >
			vector_measure(arr[i].x, arr[i].y, player.x, player.y))
				objs_swap(&arr[j], &arr[i]);
			j++;
		}
		i++;
	}
}

/*
** Go through every items in the now sector,
** and stock in drawable the ones that will be drawn
*/

int			go_through_items(t_sector now, t_player player, t_sprite *drawable,
int nbdraw)
{
	int		j;
	int		ret;
	t_float	v;
	t_float	t;

	ret = nbdraw;
	j = -1;
	while (++j < now.nbobjs && j < MAX_SPRITE)
	{
		if (now.obj[j].picked == 1)
			continue;
		v.x = (float)(now.obj[j].x - player.where.x);
		v.y = (float)(now.obj[j].y - player.where.y);
		t.x = v.x * player.anglesin - v.y * player.anglecos;
		t.y = v.x * player.anglecos + v.y * player.anglesin;
		if (t.y <= 0)
			continue ;
		drawable[ret++] = (t_sprite){now.obj[j].x, now.obj[j].y,
		now.obj[j].type, t.x, t.y, 0};
	}
	return (ret);
}

/*
** Go through every enemies in the now sector,
** and stock in drawable the ones that will be drawn
*/

int			go_through_enemies(t_sector now, t_player player,
t_sprite *drawable, int nbdraw)
{
	int		j;
	int		ret;
	t_float	v;
	t_float	t;

	ret = nbdraw;
	j = -1;
	while (++j < now.nbenem && j < MAX_SPRITE)
	{
		if (now.enem[j].life == 0)
			continue;
		v.x = (float)(now.enem[j].x - player.where.x);
		v.y = (float)(now.enem[j].y - player.where.y);
		t.x = v.x * player.anglesin - v.y * player.anglecos;
		t.y = v.x * player.anglecos + v.y * player.anglesin;
		if (t.y <= 0)
			continue ;
		drawable[ret++] = (t_sprite){now.enem[j].x,
		now.enem[j].y, now.enem[j].type, t.x, t.y, 1};
	}
	return (ret);
}
