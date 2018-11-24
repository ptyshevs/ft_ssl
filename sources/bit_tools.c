/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_shifts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:10:53 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/24 14:10:54 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "tools.h"

/*
** circular left shift of <w>-bit word
*/

t_ull	rotl(t_ull val, t_ull shift, t_ull w)
{
	return (((val << shift) | (val >> (w - shift))) & (w == 32 ? M32 : M64));
}

/*
** circular right shift of <w>-bit word
*/

t_ull	rotr(t_ull val, t_ull shift, t_ull w)
{
	return (((val >> shift) | (val << (w - shift))) & (w == 32 ? M32 : M64));
}


/*
** @brief      Rotate bits in a number, preventing overflow using mask.
**
** @note       Used in subkeys generation (DES-CBC)
**
** @param      num    The number
** @param      mask   The mask
** @param      shift  The shift
** @param      left   Whether to perform left or right rotation
**
** @return     Number with bits rotated
*/

t_ull	ft_rot(t_ull num, t_ull mask, int shift, t_bool left)
{
	if (left)
		return (((num << shift) | (num >> (28 - shift))) & mask);
	else
		return (((num >> shift) | (num << (28 - shift))) & mask);
}

/*
** Bit shift
*/

t_ull	shr(t_ull val, t_ull shift, t_ull mask)
{
	return ((val >> shift) & mask);
}

t_ull	shl(t_ull val, t_ull shift, t_ull mask)
{
	return ((val << shift) & mask);
}
