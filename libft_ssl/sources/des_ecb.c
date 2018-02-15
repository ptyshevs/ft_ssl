/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:58:45 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/15 12:19:54 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"
#include "tools.h"
#include <fcntl.h>

unsigned long	split_block(t_ull block, t_bool left)
{
	return ((left ? block >> 32 : block) & 0xFFFFFFFF);
}

t_ull		swap_bits(t_ull block, int i, int j)
{
	t_uc a = (block >> i) & 1;
	t_uc b = (block >> j) & 1;
	ft_printf("a = %d | b = %d\n", a, b);
	ft_printf("cleaning ith bit: %llb\n", block & (~(1 << i)));
	block = (block & (~(1 << i))) | (b << i);
	ft_printf("set ith bit to b: %llb\n", block);
	ft_printf("cleaning jth bit: %llb\n", block & (~(1 << j)));
	block = (block & (~(1 << j))) | (a << j);
	ft_printf("set jth bit to a: %llb\n", block);
	return (block);
}

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
** @brief      Rotate bits in number, trimming it using mask
**
** @param      num    The number
** @param      mask   The mask
** @param      shift  The shift
** @param      left   Whether to perform left or right rotation
**
** @return     Number with bits rotated
*/

unsigned long long ft_rot(unsigned long long num, unsigned long long mask,
					int shift, t_bool left)
{
	if (left)
		return (((num << shift) | (num >> (28 - shift))) & mask);
	else
		return (((num >> shift) | (num << (28 - shift))) & mask);
}

void get_subkeys(t_ull *keys, t_ull key)
{
	int		i;
	t_ull	left;
	t_ull	right;

	// ft_printf("key: %064llb\n", key);
	key = key_permut(key);
	// ft_printf("pc1 permutation: %056llb\n", key);
	left = (key >> 28) & 0xFFFFFFF;
	right = key & 0xFFFFFFF;
	i = 0;
	// ft_printf("L: %028llb | R: %028llb\n", left, right);
	while (i < 16)
	{
		left = ft_rot(left, 0xFFFFFFF, g_key_shift[i], TRUE);
		right = ft_rot(right, 0xFFFFFFF, g_key_shift[i], TRUE);
		// ft_printf("C%02d: %028llb | D%02d: %028llb\n", i + 1, left, i + 1, right);
		keys[i] = key_compress_permut((left << 28) | right);
		// ft_printf("K%02d: %048llb\n", i + 1, keys[i]);
		i++;
	}
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
** @brief      Apply Feistel function to the given 32-bit block
**
**             This operation consists of four stages:
**
**             1) Expansion: the 32-bit block is expanded to 48 bits
**             by duplicating half of the bits
**
**             2) Key mixing: output is XORed with a subkey
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
	t_ull	res;
	// ft_printf("apply subkey to block: %032llb\n", block);
	block = expand_block(block);
	// ft_printf("block expanded: %048llb\n", block);
	t_ull xored = block ^ subkey;
	// ft_printf("xored: %048llb\n", xored);
	res = 0;
	i = 0;
	while (i < 8)
	{
		int shift = 6 * (8 - i);
		// ft_printf("shift: %d | shifted mask: %llb\n", shift, 63UL << (shift - 6));
		t_ull sextet = (xored & (63UL << (shift - 6))) >> (shift - 6);
		int row = (((sextet & 32) << 1) >> 5) + (sextet & 1);
		// ft_printf("sextet & 30: %llb\n", sextet & 30);
		int col = (sextet & 30) >> 1;
		// ft_printf("sextet: %llb | row: %d | col: %d\n", sextet, row, col);
		res = (res << 4) | g_sboxes[i++][row][col];
	}
	res = pbox_permut(res);
	return (res);
}

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

void	block_to_str(t_ull block, t_uc *str, int j)
{
	int	i;

	i = 0;
	while (i < 8)
		str[j++] = (block >> (8 * (8 - i++ - 1))) & 0xFF;
}

t_ull	str_to_block(char *str)
{
	t_ull	block;
	int		i;

	block = 0;
	i = 0;
	while (i++ < 8)
		block = (block << 8) | *str++;
	return (block);
}

t_ull	des_ecb_encrypt_block(t_ull *keys, t_ull block)
{
	t_ull	left;
	t_ull	left_prev;
	t_ull	right;
	t_ull	right_prev;
	int		i;

	block = init_permut(block);
	i = 0;
	left = split_block(block, TRUE);
	left_prev = left;
	right = split_block(block, FALSE);
	right_prev = right;
	while (i < 16)
	{
		left = right;
		// ft_printf("left: %llb\n", left);
		// printf("right: %llX\n", apply_key(right_prev, keys[i]));
		// printf("apply_key to right: %d\n", apply_key(right_prev, keys[i]) == 0xFFFFFFFFBB23774CULL);
		// ft_printf("%64llb\n", left_prev ^ apply_key(right_prev, keys[i]));
		right = left_prev ^ apply_key(right_prev, keys[i]);
		// ft_printf("L%02d: %032llb | R: %032llb\n", i + 1, left, right);
		left_prev = left;
		right_prev = right;
		i++;
	}
	block = final_permut((right << 32) | left);
	// ft_printf("final L: %032llb\nR: %032llb\n", left, right);
	return (block);
}

t_ull	add_padding(char *remainder, int value)
{
	t_ull	block;
	int		i;

	block = 0;
	i = 0;
	while (*remainder)
	{
		block = (block << 8) | *remainder++;
		i++;
	}
	while (i++ < 8)
		block = (block << 8) | value;
	return (block);
}

char	*des_ecb_encrypt(t_options *options, char *in, int len)
{
	t_uc	*out;
	t_ull	keys[16];
	int		i;
	t_ull	block;

	get_subkeys(keys, options->key);
	out = (t_uc *)ft_strnew(len + (len % 8 == 0 ? 8 : 8 - (len % 8)));
	i = 0;
	while ((len -= 8) >= 0)
	{
		block = str_to_block(in);
		// ft_printf("block:\t\t%064llb\n", block);
		in += 8;
		block = des_ecb_encrypt_block(keys, block);
		// ft_printf("block encrypted:\t\t%064llb\n", block);
		block_to_str(block, out, i);
		i += 8;
	}
	block = add_padding(in, 8 + len == 0 ? 8 : -len);
	block_to_str(des_ecb_encrypt_block(keys, block), out, i);
	// if (options->base64)
	// {
	// 	in = base64_encrypt(out, ft_slen((char *)out));
	// 	free(out);
	// }
	// return (options->base64 ? in : (char *)out);
	return ((char *)out);
}

char	*des_ecb_decrypt(t_options *options, char *in, int len)
{
	(void)options;
	(void)len;
	(void)in;
	return (NULL);
}

/*
** @brief      DES (Data Encryption Standard) symmetric-key block cipher
**
** @param      options  The options
**
** @return     1 if everything okay, anything else otherwise
*/

int		des_ecb(t_options *options)
{
	char	*in;
	char	*out;
	char	*tmp;

	in = read_fd(options->fd_from);
	if (!options->key_provided)
		read_key(options);
	out = options->encrypt ?	des_ecb_encrypt(options, in, ft_slen(in)) :
								des_ecb_decrypt(options, in, ft_slen(in));
	if (out)
	{
		if (options->base64)
		{
			tmp = out;
			out = base64_encrypt((t_uc *)out, ft_slen(out));
			free(tmp);
		}
		options->base64 ?	output_base64(options->fd_to, out, options->encrypt) :
							ft_dprintf(options->fd_to, "%s", out);
	}
	free(out);
	return (1);
}
