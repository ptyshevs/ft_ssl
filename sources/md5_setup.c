/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:13:15 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/22 23:13:29 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "tools.h"
#include "math.h"
#include "md5.h"

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
** Place total number of bits
** Be careful. We store number of bits in 64-bit variable, then split it into
** two 32-bit words [64bit val] = [high_order 32bit][low_order 32bit].
** **Put low-ordered word before the high_order**
*/

void	md5_message_size(t_inp *inp, t_uc *len)
{
	int		i;
	t_ull	bits_size;
	t_uint	low_order;
	t_uint	high_order;

	bits_size = inp->bytes_total * 8;
	low_order = (t_uint)(bits_size & 0x00000000FFFFFFFFL);
	high_order = (t_uint)((bits_size & 0xFFFFFFFF00000000L) >> 32);
	i = 3;
	while (i >= 0)
	{
		len[i] = (t_uc)((low_order >> (8 * i)) & 0xFF);
		len[4 + i] = (t_uc)((high_order >> (8 * i)) & 0xFF);
		i--;
	}
}

/*
** When padding is congruent (message size is 56 modulo 64) or greater, block is reallocated and 64 bytes are added
*/

void    congruent_padding(t_inp *inp)
{
    int     write_idx;
    t_uc	*len;
    int		j;


    inp->block = ft_realloc(inp->block, sizeof(t_uc) * 64, sizeof(t_uc) * 128, True);
    inp->block_size = 128;
    write_idx = inp->block_bytes;
    inp->block[write_idx++] = 128;
    while (write_idx < 120)
        inp->block[write_idx++] = 0;
    len = ft_memalloc(sizeof(t_uc) * 8);
    md5_message_size(inp, len);
    j = 0;
    while (write_idx < 128)
        inp->block[write_idx++] = len[j++];
    ft_memdel((void **)&len);
}

/*
** Add padding to the message
*/

void	md_padding(t_inp *inp)
{
	int		i;
	int		j;
	t_uc	*len;

	i = inp->block_bytes;
	if (i >= 56)
        return congruent_padding(inp);
	inp->block[i++] = 128;
	while (i < 56)
		inp->block[i++] = 0;
	len = ft_memalloc(sizeof(t_uc) * 8);
	md5_message_size(inp, len);
	j = 0;
	while (i < 64)
		inp->block[i++] = len[j++];
	ft_memdel((void **)&len);
}


