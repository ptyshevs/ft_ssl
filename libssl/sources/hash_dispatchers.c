/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_dispatchers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:12:52 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/22 23:13:00 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "tools.h"
#include "md5.h"


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
	md5_show_digest(opt, state);
}

void	sha_dispatch(t_options *opt, t_inp *inp)
{
}

void	whirlpool_dispatch(t_options *opt, t_inp *inp)
{

}