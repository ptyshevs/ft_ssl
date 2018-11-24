/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:09:03 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 15:28:37 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <permutations.h>
#include "ft_ssl.h"

/*
** @brief      Write block to t_line <out> string. If it's the last block, add
**             PKCS padding.
**
** @note       Block is splitted into 8 bytes, each represents one unsigned
**             char to append to <out> string.
**
** @param      block       The 64-bit block
** @param      out         The out t_line
** @param      j           iterator value that points to the end of out->str
** @param      last_block  True if it is the last block, otherwise False
*/

void	block_to_str(t_ull block, t_line *out, int j, t_bool last_block)
{
	int		i;
	int		cap;

	i = 0;
	cap = (int)(last_block ? 8 - (block & 0xFF) : 8);
	if (last_block && cap % 8 == 0)
		cap = 0;
	while (i < cap)
		out->str[j++] = (t_uc)((block >> (8 * (8 - i++ - 1))) & 0xFF);
	out->len -= last_block ? (int)out->str[out->len - 1] : 0;
}



/*
** @brief      Generate 16 48-bit subkeys.
**
** @note       Algorithm steps:
**             1) Permut Key according to PC-1 table.
**             2) Split key into two 28-bit halves.
**             3) For 16 rounds, shift separatedly left and right half accroding
**                to the number of left shifts in g_key_shift table
**             4) Concatenate each pair back, and apply compressing permutation,
**                according to the PC-2 table
**
** @param      keys     The pointer to array in which the subkeys should be
**                          written.
** @param      key      The original 64-bit key
** @param      encrypt  True, if subkeys are for encryption. If False, the order
**                      of subkeys is reversed.
**
** @return     Pointer to <keys>
*/

t_ull	*get_subkeys(t_ull *keys, t_ull key, t_bool encrypt)
{
	int		i;
	t_ull	left;
	t_ull	right;

	key = key_permut(key);
	left = (key >> 28) & 0xFFFFFFF;
	right = key & 0xFFFFFFF;
	i = 0;
	while (i < 16)
	{
		left = ft_rot(left, 0xFFFFFFF, g_key_shift[i], True);
		right = ft_rot(right, 0xFFFFFFF, g_key_shift[i], True);
		keys[encrypt ? i : 15 - i] = key_compress_permut((left << 28) | right);
		i++;
	}
	return (keys);
}

/*
** @brief      Expand 32-bit block to 48 bit
**
** @param      block  The block
**
** @return     48-bit block
*/

t_ull	expand_block(t_ull block)
{
	t_ull	res;
	int		i;
	int		shift;

	res = 0;
	i = 0;
	while (i < 48)
	{
		shift = 32 - g_expand_permut[i++];
		res = (res << 1) | ((block & (1UL << shift)) >> shift);
	}
	return (res);
}

/*
** @brief      Apply Feistel function to the given 32-bit block
**
**             This operation consists of four stages:
**
**             1) Expansion: the 32-bit block is expanded to 48 bits
**             by duplicating half of the bits
**
**             2) Key mixing: output is XORed with a provided subkey
**
**             3) Substitution: block is divided into eight 6-bit pieces, for
**             each the corresponding 4-bit substitution table is applied. The
**             leftmost and rightmost bits constitute a 2-bit row number, 4 bits
**             inside form a column. For example: S(011011) will extract first
**             and last bit: (|0|1101|1|) = |01| = first row. 1101 = 13th column
**             Such non-linear substitution is the core of DES security.
**
**             4) Permutation: 32-bit output is rearranged according to the
**             final permutation table to splead bits of each S-box across four
**             different S-boxed.
**
** @param      block  The block
** @param      key    The key
**
** @return     Transformed block
*/

t_ull	apply_key(t_ull block, t_ull subkey)
{
	int		i;
	int		shift;
	t_ull	res;
	t_ull	row;
	t_ull	sextet;

	block = expand_block(block) ^ subkey;
	res = 0;
	i = 0;
	while (i < 8)
	{
		shift = 6 * (8 - i);
		sextet = (block & (63UL << (shift - 6))) >> (shift - 6);
		row = (((sextet & 32) << 1) >> 5) + (sextet & 1);
		res = (res << 4) | g_sboxes[i++][row][(sextet & 30) >> 1];
	}
	res = pbox_permut(res);
	return (res);
}
