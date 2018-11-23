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

#include "ft_printf.h"
#include "structures.h"
#include "tools.h"
#include "md5.h"

/*
** Display digest using appropriate formatting
**
** @param: hash_algo - hash algorithm in the same formatting as the original
**     for example, "MD5" or "SHA1"
*/

void	show_digest(t_options *opt, t_inp *inp, char *hash_algo, t_uc *digest)
{
	if (opt->quiet)
		ft_printf("%s\n", digest);
	else if (opt->reverse)
	{
		if (inp->src->is_stream)
			ft_printf("%s %s\n", digest, inp->src->string); // filename
		else
			ft_printf("%s \"%s\"\n", digest, inp->src->string);
	}
	else
	{
		if (inp->src->is_stream)
			ft_printf("%s(%s) = %s\n", hash_algo, inp->src->string, digest);
		else
			ft_printf("%s(\"%s\") = %s\n", hash_algo, inp->src->string, digest);
	}
}

void	md5_cleanup(t_uc	**aoutput, t_md5 **astate)
{
	ft_memdel((void **)astate);
	ft_memdel((void **)aoutput);

}

void	md5_dispatch(t_options *opt, t_inp *inp)
{
	t_md5	*state;
	t_bool	finished;
	t_uc	*output;

	state = init_state();
	finished = False;
	while (!finished && next_block(inp))
	{
		if ((t_uint)inp->block_bytes < inp->block_size)
		{
			finished = True;
			md5_padding(inp);
		}
		md5_block(inp, state);
	}
	if (!finished)  // (s)read failed
	{
		ft_memdel((void **)&state);
		return bad_read_error(inp->src->string);
	}
//	show_block(inp);
	output = md5_collect_digest(state);
	show_digest(opt, inp, "MD5", output);
	md5_cleanup(&output, &state);
}

void	sha_dispatch(t_options *opt, t_inp *inp)
{
	(void)opt;
	(void)inp;
}

void	whirlpool_dispatch(t_options *opt, t_inp *inp)
{
	(void)opt;
	(void)inp;
}