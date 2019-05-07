/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/21 22:03:21 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 21:03:57 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

static void	add_equal(t_content **temp, int j)
{
	t_content	*cont;

	cont = *temp;
	cont->c_title[j++] = ' ';
	cont->c_title[j++] = '=';
	cont->c_title[j++] = ' ';
}

static void	get_lis_num(t_content **con, t_lis *vert)
{
	t_content	*temp;
	t_lis		*tmp;
	int			i;
	int			j;
	char		*str;

	tmp = vert;
	i = 1;
	j = 0;
	temp = *con;
	while (tmp && tmp->text != -1)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	str = ft_itoa(i);
	i = 0;
	while (temp->c_title[j])
		j++;
	while (str[i])
		temp->c_title[j++] = str[i++];
	add_equal(&temp, j);
	ft_strdel(&str);
}

void		get_title(t_edit *edit, t_content *con)
{
	t_sec		*hl;

	hl = edit->hl_sec;
	if (hl->gravity == -1)
		fill_str_content(256, con->c_title, GRAVITY);
	if (hl->floor == -1)
		fill_str_content(256, con->c_title, FLOOR);
	else if (hl->ceil == -1)
		fill_str_content(256, con->c_title, CEIL);
	else if (check_lis_input(hl->vert))
	{
		fill_str_content(256, con->c_title, VEC);
		get_lis_num(&con, hl->vert);
	}
	else if (check_lis_input(hl->obj))
	{
		fill_str_content(256, con->c_title, OBJ);
		get_lis_num(&con, hl->obj);
	}
	else if (check_lis_input(hl->enem))
	{
		fill_str_content(256, con->c_title, ENEM);
		get_lis_num(&con, hl->enem);
	}
}
