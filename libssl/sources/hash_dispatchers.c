
#include <ft_printf.h>
#include "ft_ssl.h"

void	md5_dispatch(t_options *opt, t_inp *inp)
{
	ft_printf("md5 dispatch called, input block: %s\n", inp->block);
	next_block(inp);
	ft_printf("md5 dispatch called, input block: %s\n", inp->block);
}

void	sha_dispatch(t_options *opt, t_inp *inp)
{

}

void	whirlpool_dispatch(t_options *opt, t_inp *inp)
{

}