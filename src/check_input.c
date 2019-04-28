/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 17:22:48 by nzenzela     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 15:02:12 by nzenzela    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/doom.h"

char	*check_num(int num)
{
	if (num == 48)
		return (_0_);
	else if (num == 49)
		return (_1_);
	else if (num == 50)
		return (_2_);
	else if (num == 51)
		return (_3_);
	else if (num == 52)
		return (_4_);
	else if (num == 53)
		return (_5_);
	else if (num == 54)
		return (_6_);
	else if (num == 55)
		return (_7_);
	else if (num == 56)
		return (_8_);
	else if (num == 57)
		return (_9_);
	else
		return (0);
}

char	*check_alpha1(int num)
{
	if (num == 97)
		return (_A_);
	else if (num == 98)
		return (_B_);
	else if (num == 99)
		return (_C_);
	else if (num == 100)
		return (_D_);
	else if (num == 101)
		return (_E_);
	else if (num == 102)
		return (_F_);
	else if (num == 103)
		return (_G_);
	else if (num == 104)
		return (_H_);
	else if (num == 105)
		return (_I_);
	else if (num == 106)
		return (_J_);
	else
		return (0);
}

char	*check_alpha2(int num)
{
	if (num == 107)
		return (_K_);
	else if (num == 108)
		return (_L_);
	else if (num == 109)
		return (_M_);
	else if (num == 110)
		return (_N_);
	else if (num == 111)
		return (_O_);
	else if (num == 112)
		return (_P_);
	else if (num == 113)
		return (_Q_);
	else if (num == 114)
		return (_R_);
	else if (num == 115)
		return (_S_);
	else if (num == 116)
		return (_T_);
	else
		return (0);
}

char	*check_alpha3(int num)
{
	if (num == 117)
		return (_U_);
	else if (num == 118)
		return (_V_);
	else if (num == 119)
		return (_W_);
	else if (num == 120)
		return (_X_);
	else if (num == 121)
		return (_Y_);
	else if (num == 122)
		return (_Z_);
	else
		return (0);
}
