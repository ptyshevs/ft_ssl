/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:37:46 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/21 12:05:15 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"

/*
** @brief      Initial permutation
**
** @param      block  The block
**
** @return     permuted block
*/

t_ull		init_permut(t_ull block)
{
	t_ull	res;
	int		i;
	int		shift;

	res = 0;
	i = 0;
	while (i < 64)
	{
		shift = 64 - g_init_permut[i++];
		res = (res << 1) | ((block & (1UL << shift)) >> shift);
	}
	return (res);
}

/*
** @brief      Permute key according to the PC-1 table
**
** @param      key   The 64-bit key
**
** @return     56-bit permuted key
*/

t_ull	key_permut(t_ull key)
{
	t_ull	res;
	int		i;
	int		shift;

	res = 0;
	i = 0;
	while (i < 56)
	{
		shift = 64 - g_key_permut[i++];
		res = (res << 1) | ((key & (1UL << shift)) >> shift);
	}
	return (res);
}

/*
** @brief      Compress 48-bit block back to 32-bits
**
** @param      key   The key
**
** @return     32-bit key block
*/

t_ull	key_compress_permut(t_ull key)
{
    t_ull	res;
    int		i;
    int		shift;

    res = 0;
    i = 0;
    while (i < 48)
    {
        shift = 56 - g_compress_permut[i++];
        res = (res << 1) | ((key & (1UL << shift)) >> shift);
    }
    return (res);
}

/*
** @brief      Permute 32-bit 
**
** @param      block  The block
**
** @return     P-box permuted block
*/

t_ull	pbox_permut(t_ull block)
{
	t_ull	res;
	int		i;
	int		shift;

	res = 0;
	i = 0;
	while (i < 32)
	{
		shift = 32 - g_pbox_permut[i++];
		res = (res << 1) | ((block & (1UL << shift)) >> shift);
	}
	return (res);
}

/*
** @brief      Final permutation of RL block
**
** @param      block  The block
**
** @return     { description_of_the_return_value }
*/

t_ull	final_permut(t_ull block)
{
    t_ull	res;
    int		i;
    int		shift;

    res = 0;
    i = 0;
    while (i < 64)
    {
        shift = 64 - g_final_permut[i++];
        res = (res << 1) | ((block & (1UL << shift)) >> shift);
    }
    return (res);
}

