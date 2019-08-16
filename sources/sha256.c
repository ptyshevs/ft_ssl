/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:10:49 by ptyshevs          #+#    #+#             */
/*   Updated: 2019/08/16 20:52:14 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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

void	sha_collect_words(t_inp *inp, t_sha *st)
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
//    t_sha	*state;
//    int		i;
//
//    state = ft_memalloc(sizeof(t_md5));
//    state->A = 0x67452301;
//    state->B = 0xefcdab89;
//    state->C = 0x98badcfe;
//    state->D = 0x10325476;
//    i = 1;
//    while (i <= 64)
//    {
//        state->M[i - 1] = (t_uint)floor(fabs(sin(i)) * (1L << 32)); // correct
//        i++;
//    }
}

t_sha   *init_sha(void)
{
    t_sha   *state;
    int     i;

    state = ft_memalloc(sizeof(t_sha));
    state->H = ft_memalloc(sizeof(t_uint) * 8);

    i = 0;
    while (i < 8)
    {
        state->H[i] = g_sha256_h0[i];
        i++;
    }
    i = 0;
    while (i < 64)
    {
        state->M[i] = g_sha256_k[i];
        i++;
    }
    return (state);
}