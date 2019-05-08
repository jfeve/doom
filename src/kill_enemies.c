/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   kill_enemies.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 12:27:18 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 12:52:46 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

/*
** Check if the enemy is on the middle of the screen
*/

static int	check_middle_in(t_sprite sprite, SDL_Surface *enemy[2], t_point p,
float distance)
{
	t_point	i;
	int		nnw;
	t_point	n;

	i.y = p.y - 1;
	i.x = p.x;
	n.x = enemy[sprite.type - 1]->w * (32 / distance);
	n.y = enemy[sprite.type - 1]->h * (32 / distance);
	while (++i.y < p.y + n.y)
	{
		if (i.y - p.y < n.y / 5)
		{
			i.x = p.x + 2 * n.x / 5 - 1;
			nnw = 4 * n.x / 5;
		}
		else
		{
			i.x = p.x - 1;
			nnw = n.x;
		}
		while (++i.x < p.x + nnw)
			if (i.y == RWIN_H / 2 && i.x == RWIN_W / 2)
				return (1);
	}
	return (0);
}

/*
** Pick the enemy to kill and delete him
** t_xyz p is here for the norm, x and y are ints and z is the distance
*/

int			kill_enemies(t_sector *sec, t_sprite sprite, SDL_Surface *enemy[2],
t_xyz p)
{
	int		i;

	if (sprite.is_enemy && check_middle_in(sprite, enemy, (t_point){(int)p.x
	- (enemy[sprite.type - 1]->w / 2), (int)p.y - (enemy[sprite.type
	- 1]->h / 2) - (1300.0f / p.z)}, p.z))
	{
		i = 0;
		while (i < sec->nbenem)
		{
			if ((int)sec->enem[i].x == sprite.x && (int)sec->enem[i].y
			== sprite.y)
				sec->enem[i].life = 0;
			i++;
		}
		return (1);
	}
	return (0);
}
