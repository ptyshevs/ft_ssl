/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_communicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:13:04 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/22 23:13:09 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ft_printf.h"

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
	int		i;

	i = 0;
	while (i < 64)
	{
		ft_printf("%08b ", inp->block[i]);
		if (i > 1 && i % 8 == 7)
			ft_printf("\n");
		i++;
	}
}

/*
** Since md5 returns small-endian blocks, we need to convert them back to
** big-endian, i.e. the most significant *byte* is the first one, etc.
**   Thus, for 32-bit int, that consists of byte 1, 2, 3, and 4:
**    1 -> 4
**    2 -> 3
**    3 -> 2
**    4 -> 1
*/

static t_uint	to_big_endian(t_uint val)
{
	return (((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) |
			((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24));
}


/*
** Collect output from md5 into string digest
** Don't forget to free
*/

t_uc	*md5_collect_digest(t_md5 *state)
{
	t_uc	*res;

	res = (t_uc *)ft_sprintf("%08x%08x%08x%08x",
			to_big_endian(state->A),
			to_big_endian(state->B),
			to_big_endian(state->C),
			to_big_endian(state->D));
	return (res);
}

