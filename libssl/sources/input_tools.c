
#include "tools.h"

/*
 * Same as read, but from string
 * (used for processing -s flag in the same fashion)
 */

int		sread(const t_uc *str, void *to, ssize_t size)
{
	static int	pos;
	t_uint		i;

	if (!to)
		pos = 0;
	if (!str)
		return (-1);
	i = 0;
	while (str[pos] && i < size)
	{
		((char *)to)[i] = str[pos];
		i++;
		pos++;
	}
	return (i);
}

/*
 * Read next block from the input source
 */

void	next_block(t_inp *inp)
{
	if (inp->fd_from >= 0)
		inp->block_bytes = (int)read(inp->fd_from, inp->block, inp->block_size);
	else
		inp->block_bytes = sread(inp->buffer, inp->block, inp->block_size);
	if (inp->block_bytes < 0)
	inp->bytes_total += inp->block_bytes;
}

/*
 * Initialize input structure, store block size and read first block
 */

t_inp		*init_input(t_command *command, t_options *opt, t_inp_src *src)
{
	t_inp	*inp;

	inp = ft_memalloc(sizeof(t_inp));
	inp->fd_from = src->fd;
	inp->fd_to = opt->fd_to;
	inp->block_size = command->block_size;
	inp->block = ft_memalloc(sizeof(t_uc) * inp->block_size);
	inp->buffer = src->is_stream ? NULL : (t_uc *)src->string;
	return (inp);
}