
#include <ft_printf.h>
#include <ft_str.h>
#include "tools.h"

/*
 * Copy bytes from buffer into block
 * (used for processing -s flag in the same fashion)
 */

int		buf_read(t_inp *inp)
{
	t_uint		i;

	if (!inp->buffer)
		return (-1);
	i = 0;
	while (inp->pos < inp->buf_size && i < inp->block_size)
	{
		((char *)inp->block)[i] = inp->buffer[inp->pos];
		i++;
		inp->pos++;
	}
	return (i);
}

/*
** Basically, wrapper around buf_read to refresh buffer if necessary.
** Notes:
**    this is so easy mainly because buf_size is a multiple of block_size
*/

int		file_read(t_inp *inp)
{
	ssize_t		read_ret;

	if (inp->pos == inp->buf_size)
	{
		read_ret = (int)read(inp->src->fd, inp->buffer,
								inp->block_size * BUF_MULT);
		inp->pos = 0;
		if (read_ret == -1)
			return (-1);
		else
			inp->buf_size = (t_uint)read_ret;
	}
	return buf_read(inp);
}

/*
 * Read next block from the input source
 *
 * @return: True if read successfully, else False
 */

t_bool	next_block(t_inp *inp)
{
	if (inp->src->fd >= 0)
		inp->block_bytes = file_read(inp);
	else
		inp->block_bytes = buf_read(inp);
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
	if (src->is_stream)
		inp->buffer = ft_memalloc(sizeof(t_uc) * inp->block_size * BUF_MULT);
	else
	{
		// string is strdup'ed, so no problem freeing this after processing
		inp->buffer = (t_uc *)src->string;
		inp->buf_size = (int)ft_slen(src->string);
	}
	return (inp);
}