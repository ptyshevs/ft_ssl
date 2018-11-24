/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:13:33 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/22 23:13:37 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <ft_strnum.h>
#include <ft_printf.h>
#include "tools.h"
#include "md5.h"

void	apply_shift(t_md5 *st, int i, t_uint (*f)(t_uint, t_uint, t_uint))
{
	t_uint	sum;

	if (i % 4 == 0)
	{
		sum = st->A + f(st->B, st->C, st->D) + st->X[g_md5_trans[i]] + st->M[i];
		st->A = st->B + (t_uint)rotl(sum, g_md5_shifts[i], 32);
	}
	else if (i % 4 == 1)
	{
		sum = st->D + f(st->A, st->B, st->C) + st->X[g_md5_trans[i]] + st->M[i];
		st->D = st->A + (t_uint)rotl(sum, g_md5_shifts[i], 32);
	}
	else if (i % 4 == 2)
	{
		sum = st->C + f(st->D, st->A, st->B) + st->X[g_md5_trans[i]] + st->M[i];
		st->C = st->D + (t_uint)rotl(sum, g_md5_shifts[i], 32);
	}
	else
	{
		sum = st->B + f(st->C, st->D, st->A) + st->X[g_md5_trans[i]] + st->M[i];
		st->B = st->C + (t_uint)rotl(sum, g_md5_shifts[i], 32);
	}
}

void	collect_words(t_inp *inp, t_md5 *st)
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

/*
 * COMMENT THIS
 */

void	md5_block(t_inp *inp, t_md5 *st)
{
	int		i;

	st->A_prev = st->A;
	st->B_prev = st->B;
	st->C_prev = st->C;
	st->D_prev = st->D;
	collect_words(inp, st);
	i = 0;
	while (i < 64)
	{
//		ft_printf("A[%08x] | i[%d] | k[%d] s[%d]\n", st->A, i, g_md5_trans[i], g_md5_shifts[i]);
		if (i < 16)
			apply_shift(st, i, F);
		else if (i < 32)
			apply_shift(st, i, G);
		else if (i < 48)
			apply_shift(st, i, H);
		else
			apply_shift(st, i, I);
		i++;
	}
	st->A += st->A_prev;
	st->B += st->B_prev;
	st->C += st->C_prev;
	st->D += st->D_prev;
}
