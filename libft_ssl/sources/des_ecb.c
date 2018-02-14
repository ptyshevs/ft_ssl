/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:58:45 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/14 12:11:38 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"
#include "tools.h"
#include <fcntl.h>

void	initial_permutation(t_block *block)
{
	int	i;
	// int	bit;

	i = 0;
	while (i < 64)
	{
		// bit1 = block->b & (1 << g_init_permut[i]);
		int bit2 = *block & (1 << (64 - i));
		ft_printf("current bit is %d\n", bit2);
		i++;
	}
}

unsigned long	split_block(t_block block, t_bool left)
{
	return ((left ? block >> 32 : block) & 0xFFFFFFFF);
}

t_block		swap_bits(t_block block, int i, int j)
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

t_block		init_permut(t_block block)
{
	t_block	res;
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

unsigned long ft_rot(unsigned long num, int shift, t_bool left)
{
	unsigned long mask;

	mask = num <<
}

void get_subkeys(t_block *keys, t_ull key)
{
	int		i;
	t_ull	left;
	t_ull	right;

	ft_printf("key: %064llb\n", key);
	key = key_permut(key);
	ft_printf("pc1 permutation: %064llb\n", key);
	left = (key >> 32) & 0xFFFFFFFF;
	right = key & 0xFFFFFFFF;
	i = 0;
	while (i < 16)
	{
		left = ft_rot(left, g_key_shift[i], TRUE);
	}
}

char	*des_ecb_encrypt(t_options *options, char *in)
{
	// t_block	block;
	t_block keys[16];
	// int		i;

	get_subkeys(keys, options->key);
	// block = 0x123456789ABCDEF;
	// ft_printf("block:\t\t%064llb\n", block);
	// block = init_permut(block);
	// i = 0;
	// block left = split_block(block, TRUE);
	// block left_prev = left;
	// block right = split_block(block, FALSE);
	// block right_prev = right;
	// while (i < 16)
	// {
	// 	left = right;
	// 	right = left_prev + apply_key(right_prev, subkeys[i]);
	// 	left_prev = left;
	// 	right_prev = right;
	// 	i++;
	// }
//==========================================================================
	// ft_printf("init permut:\t%064llb\n", block);
	// ft_printf("L: %032llb | R: %032llb\n", split_block(block, TRUE), split_block(block, FALSE));
	// int len = ft_slen(in);
	// ft_printf("len: %d\n", len);
	// while (len - 8 >= 0 && (len -= 8))
	// {
	// 	block = 0;
	// 	int i = 8;
	// 	while (i--)
	// 		block = (block << 8) + *in++;
	// 	ft_printf("block: %llb\n", block);
	// }
	// ft_printf("len left: %d\n", len);
	// block = 
	(void)options;
	(void)in;
	return (NULL);
}

char	*des_ecb_decrypt(t_options *options, char *in)
{
	(void)options;
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

	in = read_fd(options->fd_from);
	if (!options->key_provided)
		read_key(options);
	ft_printf("key: %064llb\n", options->key);
	out = options->encrypt ?	des_ecb_encrypt(options, in) :
								des_ecb_decrypt(options, in);
	if (out)
		ft_dprintf(options->fd_to, "%s", out);
	free(out);
	return (1);
}
