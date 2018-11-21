#include <math.h>
#include <ft_strnum.h>
#include "tools.h"

/*
 * Place total number of bits
 */
void	md5_message_size(t_inp *inp, t_uc *len)
{
	int		i;
	t_ull	bits_size;

	bits_size = inp->bytes_total * 8;
	i = 0;
	while (i < 8)
	{
		t_ull val = (bits_size >> (8 * (7 - i))) & 0xFF;
		len[i] = (t_uc)val;
		i++;
	}
}

void	md5_padding(t_inp *inp)
{
	int		i;
	int		j;
	t_uc	*len;

	i = inp->block_bytes;
	inp->block[i++] = 128;
	while (i < 56)
		inp->block[i++] = 0;
	len = ft_memalloc(sizeof(t_uc) * 8);
	md5_message_size(inp, len);
//	show_len(len);
	j = 0;
	while (i < 64)
		inp->block[i++] = len[j++];
	ft_memdel((void **)&len);
}

t_uint	F(t_uint x, t_uint y, t_uint z)
{
	return ((x & y) | ((~x) & z));
}

t_uint	G(t_uint x, t_uint y, t_uint z)
{
	return ((x & z) | (y & (~z)));
}

t_uint H(t_uint x, t_uint y, t_uint z)
{
	return (x ^ y ^ z);
}

t_uint I(t_uint x, t_uint y, t_uint z)
{
	return (y ^ (x | (~z)));
}

t_uint	left_rotate(t_uint val, t_uint shift, t_uint type_len)
{
	if (shift > type_len)
		shift %= type_len;
	return ((val << shift) | (val >> (type_len - shift)));
}

void	apply_shift(t_md5 *st, int i, t_uint (*f)(t_uint, t_uint, t_uint))
{
	t_uint	sum;

	if (i % 4 == 0)
	{
		sum = st->A + f(st->B, st->C, st->D) + st->X[g_md5_trans[i]] + st->M[i];
		st->A = st->B + left_rotate(sum, g_md5_shifts[i], 32);
	}
	else if (i % 4 == 1)
	{
		sum = st->D + f(st->A, st->B, st->C) + st->X[g_md5_trans[i]] + st->M[i];
		st->D = st->A + left_rotate(sum, g_md5_shifts[i], 32);
	}
	else if (i % 4 == 2)
	{
		sum = st->C + f(st->D, st->A, st->B) + st->X[g_md5_trans[i]] + st->M[i];
		st->C = st->D + left_rotate(sum, g_md5_shifts[i], 32);
	}
	else
	{
		sum = st->B + f(st->C, st->D, st->A) + st->X[g_md5_trans[i]] + st->M[i];
		st->B = st->C + left_rotate(sum, g_md5_shifts[i], 32);
	}
}

void	collect_words(t_inp *inp, t_md5 *st)
{
	int		i;
	int		j;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 4)
			st->X[i] = (st->X[i] << 8) | inp->block[4 * i + j++];
		i++;
	}
}


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