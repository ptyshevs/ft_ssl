
#include <ft_printf.h>
#include "tools.h"

/*
 * Same as read, but from string
 * (used for processing -s flag in the same fashion)
 */

int		sread(t_inp *inp)
{
	t_uint		i;

	if (!inp->buffer)
		return (-1);
	i = 0;
	while (inp->buffer[inp->pos] && i < inp->block_size)
	{
		((char *)inp->block)[i] = inp->buffer[inp->pos];
		i++;
		inp->pos++;
	}
	return (i);
}

/*
 * Read next block from the input source
 *
 * @return: True if read successfully, else False
 */

t_bool	next_block(t_inp *inp)
{
	if (inp->src->fd >= 0)
		inp->block_bytes = (int)read(inp->src->fd, inp->block, inp->block_size);
	else
		inp->block_bytes = sread(inp);
	if (inp->block_bytes < 0)
		return (False);
//	if (inp->bits_total == 0 && inp->block_bytes > 0)
//		inp->bits_total =
	inp->bytes_total += inp->block_bytes;
	return (True);
}

/*
 * Initialize input inp->bufferucture, store block size and read first block
 */

t_inp		*init_input(t_command *command, t_inp_src *src)
{
	t_inp	*inp;

	inp = ft_memalloc(sizeof(t_inp));
	inp->src = src;
	inp->block_size = command->block_size;
	inp->block = ft_memalloc(sizeof(t_uc) * inp->block_size);
	inp->buffer = src->is_stream ? NULL : (t_uc *)src->string;
	return (inp);
}