/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:10:49 by ptyshevs          #+#    #+#             */
/*   Updated: 2019/08/17 09:54:31 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <tools.h>
#include <ft_printf.h>
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

/*
** X is M in RFC 4634 (MD5 Compatibility)
*/

void	sha_collect_words(t_inp *inp, t_sha *st)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		int j = 4 * i;
		st->X[i] = (inp->block[j] << 24) | (inp->block[j + 1] << 16) |
				(inp->block[j + 2] << 8) | (inp->block[j + 3]);
		i++;
	}
}

void	prepare_message_shedule(t_sha *st)
{
	int	i;

	i = 0;
	while (i < 64)
	{
		if (i < 16)
			st->M[i] = st->X[i];
		else//                                    This place can be i-15
			st->M[i] = SSIG1(st->M[i-2]) + st->M[i-7] + SSIG0(st->M[i-15]) + st->M[i-16];
		i++;
	}
}

void	show_internal_state(t_sha *st)
{
	int i = 0;
	while (i < st->H_size) {
		ft_printf("%08x ", st->H[i]);
		i++;
	}
	ft_printf("\n");
}

void	show_message_shedule(t_sha *st)
{
	int i = 0;
	while (i < 64)
	{
		if (i > 0 && i % 8 == 0)
			ft_printf("\n");
		ft_printf("%08x|", st->M[i]);
		i++;
	}
}

void	sha256_block(t_inp *inp, t_sha *st)
{
	t_uint	t1;
	t_uint	t2;
	int		i;

//	show_internal_state(st); //ok
	ft_memcpy(st->H_prev, st->H, st->H_size * sizeof(t_uint));
	sha_collect_words(inp, st);
	prepare_message_shedule(st);
	show_message_shedule(st);
	t_uint a = st->H[0];
	t_uint b = st->H[1];
	t_uint c = st->H[2];
	t_uint d = st->H[3];
	t_uint e = st->H[4];
	t_uint f = st->H[5];
	t_uint g = st->H[6];
	t_uint h = st->H[7];
	i = 0;
	while (i < 64)
	{
		t1 = h + BSIG1(e) + CH(e, f, g) + g_sha256_k[i] + st->M[i];
		t2 = BSIG0(a) + MAJ(a, b, c);

		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
		i++;
	}
	st->H[0] += a;
	st->H[1] += b;
	st->H[2] += c;
	st->H[3] += d;
	st->H[4] += e;
	st->H[5] += f;
	st->H[6] += g;
	st->H[7] += h;
}

t_sha   *init_sha(void)
{
	t_sha   *state;
	int     i;

	state = ft_memalloc(sizeof(t_sha));
	state->H_size = 8; // sha256
	state->H = ft_memalloc(sizeof(t_uint) * state->H_size);
	state->H_prev = ft_memalloc(sizeof(t_uint) * state->H_size);

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