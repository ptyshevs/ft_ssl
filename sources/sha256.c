/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:10:49 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/24 14:10:51 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <tools.h>
#include "sha.h"

t_uint	CH(t_uint x, t_uint y, t_uint z)
{
	return ((x & y) ^ ((~x & z)));
}

t_uint MAJ(t_uint x, t_uint y, t_uint z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

t_uint	BSIG0(t_uint x)
{
	return ((t_uint)(rotr(x, 2, 32) ^ rotr(x, 13, 32) ^ rotr(x, 22, 32)));
}

t_uint	BSIG1(t_uint x)
{
	return ((t_uint)(rotr(x, 6, 32) ^ rotr(x, 11, 32) ^ rotr(x, 25, 32)));
}

t_uint SSIG0(t_uint x)
{
	return ((t_uint)(rotr(x, 7, 32) ^ rotr(x, 18, 32) ^ shr(x, 3, M32)));
}

t_uint SSIG1(t_uint x)
{
	return ((t_uint)(rotr(x, 17, 32) ^ rotr(x, 19, 32) ^ shr(x, 10, M32)));
}

void	collect_words(t_inp *inp, t_sha *st)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		int j = 4 * i;
		st->X[i] = inp->block[j] | (inp->block[j + 1] << 8) |
				(inp->block[j + 2] << 16) | (inp->block[j + 3] << 24);
		i++;
	}
}

void	sha256_block(t_inp *inp, t_sha *st)
{
	(void)inp;
	(void)st;
	collect_words(inp, st);
}