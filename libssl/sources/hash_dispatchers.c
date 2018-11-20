
#include <ft_printf.h>
#include "ft_ssl.h"


void	md5_dispatch(t_options *opt, t_inp *inp)
{
	t_ull	digest;

	digest = 0;
	next_block(inp);
	ft_printf("md5 dispatch called, input block: %s\n", inp->block);
	if (inp->block_bytes < inp->block_size)
		md5_padding(inp);
	digest = md5_block(inp);
//	show_block(inp);
}

void	sha_dispatch(t_options *opt, t_inp *inp)
{

}

void	whirlpool_dispatch(t_options *opt, t_inp *inp)
{

}