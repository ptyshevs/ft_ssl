
#include <ft_printf.h>
#include "ft_ssl.h"

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
		int val = (bits_size >> (8 * (7 - i))) & 0xFF;
		len[i] = val;
		i++;
	}
}

void	show_len(t_uc *len)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		ft_printf("[%d]: %08b\n", i, len[i]);
		i++;
	}
}

void	show_block(t_inp *inp)
{

}

void	md5_padding(t_inp *inp)
{
	int		i;
	int		j;
	t_uc	*len;

	i = inp->block_bytes;
	inp->block[++i] = 128;
	while (i < 56)
		inp->block[i++] = 0;
	len = ft_memalloc(sizeof(t_uc) * 8);
	md5_message_size(inp, len);
	show_len(len);
	j = 0;
	while (i < 64)
		inp->block[i++] = len[j++];
	ft_memdel((void **)&len);
}

void	md5_dispatch(t_options *opt, t_inp *inp)
{
	next_block(inp);
	ft_printf("md5 dispatch called, input block: %s\n", inp->block);
	if (inp->block_bytes < inp->block_size)
		md5_padding(inp);
	show_block(inp);
}

void	sha_dispatch(t_options *opt, t_inp *inp)
{

}

void	whirlpool_dispatch(t_options *opt, t_inp *inp)
{

}