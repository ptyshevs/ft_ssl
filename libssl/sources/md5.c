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

t_uint	f(t_uint x, t_uint y, t_uint z)
{
	return ((x & y) | (~x & z));
}

t_uint	g(t_uint x, t_uint y, t_uint z)
{
	return ((x & y) | (y & ~z));
}

t_uint h(t_uint x, t_uint y, t_uint z)
{
	return (x ^ y ^ z);
}

t_uint i(t_uint x, t_uint y, t_uint z)
{
	return (y ^ (x | ~z));
}

t_md5	init_state(t_uc *block)
{
	t_md5	state;
	int		i;

	state.A = 0x01234567;
	state.B = 0x89abcdef;
	state.C = 0xfedcba98;
	state.D = 0x76543210;
	i = 0;
	while (i < 16)
	{
		state.X[i] = block[i];
		i++;
	}
	return (state);
}

t_ull	md5_block(t_inp *inp)
{
	t_ull	digest;
	t_md5	md5_state = init_state(inp->block);


	digest = 0;
	return (digest);
}