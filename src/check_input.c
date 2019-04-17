/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 17:22:48 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 18:20:59 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

char	*check_num(int num)
{
	if (num == 1)
		return (_1_);
	else if (num == 2)
		return (_2_);
	else if (num == 3)
		return (_3_);
	else if (num == 4)
		return (_4_);
	else if (num == 5)
		return (_5_);
	else if (num == 6)
		return (_6_);
	else if (num == 7)
		return (_7_);
	else if (num == 8)
		return (_8_);
	else if (num == 9)
		return (_9_);
	else if (num == 0)
		return (_0_);
	else
		return (0);
}

char	*check_alpha1(int num)
{
	if (num == 13)
		return (_A_);
	else if (num == 14)
		return (_B_);
	else if (num == 15)
		return (_C_);
	else if (num == 16)
		return (_D_);
	else if (num == 17)
		return (_E_);
	else if (num == 18)
		return (_F_);
	else if (num == 19)
		return (_G_);
	else if (num == 20)
		return (_H_);
	else if (num == 21)
		return (_I_);
	else if (num == 22)
		return (_J_);
	else
		return (0);
}

char	*check_alpha2(int num)
{
	if (num == 23)
		return (_K_);
	else if (num == 24)
		return (_L_);
	else if (num == 25)
		return (_M_);
	else if (num == 26)
		return (_N_);
	else if (num == 27)
		return (_O_);
	else if (num == 28)
		return (_P_);
	else if (num == 29)
		return (_Q_);
	else if (num == 30)
		return (_R_);
	else if (num == 31)
		return (_S_);
	else if (num == 32)
		return (_T_);
	else
		return (0);
}

char	*check_alpha3(int num)
{
	if (num == 23)
		return (_U_);
	else if (num == 24)
		return (_V_);
	else if (num == 25)
		return (_W_);
	else if (num == 26)
		return (_X_);
	else if (num == 27)
		return (_Y_);
	else if (num == 28)
		return (_Z_);
	else
		return (0);
}
