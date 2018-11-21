
#include <ft_printf.h>
#include "math.h"
#include "structures.h"
#include "tools.h"

t_md5	*init_state(void)
{
	t_md5	*state;
	int		i;

	state = ft_memalloc(sizeof(t_md5));
	state->A = 0x01234567;
	state->B = 0x89abcdef;
	state->C = 0xfedcba98;
	state->D = 0x76543210;
	i = 1;
	while (i <= 64)
	{
		state->M[i - 1] = (t_uint)fabs(sin(i) * (1L << 32));
		i++;
	}
	return (state);
}

void	show_digest(t_options *opt, t_md5 *st)
{
	ft_printf("%08x%08x%08x%08x\n", st->A, st->B, st->C, st->D);
}

void	md5_dispatch(t_options *opt, t_inp *inp)
{
	t_md5	*state;
	t_bool	finished;

	state = init_state();
	finished = False;
	while (!finished)
	{
		next_block(inp);
		if (inp->block_bytes < inp->block_size)
		{
			finished = True;
			md5_padding(inp);
		}
		md5_block(inp, state);
	}
	show_block(inp);
	show_digest(opt, state);
}

void	sha_dispatch(t_options *opt, t_inp *inp)
{

}

void	whirlpool_dispatch(t_options *opt, t_inp *inp)
{

}