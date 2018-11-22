
#include <ft_printf.h>
#include "math.h"
#include "structures.h"
#include "tools.h"

t_md5	*init_state(void)
{
	t_md5	*state;
	int		i;

	state = ft_memalloc(sizeof(t_md5));
	state->A = 0x67452301;
	state->B = 0xefcdab89;
	state->C = 0x98badcfe;
	state->D = 0x10325476;
	i = 1;
	while (i <= 64)
	{
		state->M[i - 1] = (t_uint)floor(fabs(sin(i)) * (1L << 32)); // correct
		i++;
	}
	return (state);
}

/*
** Since md5 returns small-endian blocks, we need to convert them back to
** big-endian, i.e. the most significant *byte* is the first one, etc.
*/

t_uint	to_big_endian(t_uint val)
{
	return (((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) |
			((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24));
}

void	show_digest(t_options *opt, t_md5 *st)
{
	ft_printf("%08x%08x%08x%08x\n", to_big_endian(st->A), to_big_endian(st->B),
			to_big_endian(st->C), to_big_endian(st->D));
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
			md5_padding(inp); // correct
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