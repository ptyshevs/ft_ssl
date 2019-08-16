/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_dispatchers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:12:52 by ptyshevs          #+#    #+#             */
/*   Updated: 2019/08/16 21:06:17 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_str.h>
#include <sha.h>
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
		if (inp->src->is_stream && ft_slen(inp->src->string))
			ft_printf("%s(%s) = %s\n", hash_algo, inp->src->string, digest);
		else if (inp->src->is_stream)  // stdin
			ft_printf("%s\n", digest);
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
		if (inp->src->fd == 0 && opt->stdin_append)
			write(1, inp->block, (size_t)inp->block_bytes);
		if ((t_uint)inp->block_bytes < inp->block_size)
		{
			finished = True;
			md_padding(inp);
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

/*
** TODO make init state work for both md5 and sha
*/

//t_state	*base_init_state(char *command)
//{
//	t_state		*st;
//
//	st = ft_memalloc(sizeof(t_state));
//	return (st);
//}

void	sha_cleanup(t_uc **aoutput, t_sha **astate)
{
	ft_memdel((void **)aoutput);
	ft_memdel((void **)&(*astate)->H);
	ft_memdel((void **)astate);
}

/*
 * Directly copy-pasted from md5_communicate
 */
static t_uint	to_big_endian(t_uint val)
{
	return (((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) |
			((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24));
}

t_uc	*sha_collect_digest(t_sha *state)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (i < 8)
	{
		res = ft_concat(res, ft_sprintf("%08x", to_big_endian(state->H[i])), True);
		i++;
	}
	return ((t_uc *)res);
}

void	sha_dispatch(t_options *opt, t_inp *inp)
{
	t_sha	*state;
	t_bool	finished;
	t_uc	*output;

	state = init_sha();
	finished = False;
	while (!finished && next_block(inp))
	{
		if (inp->src->fd == 0 && opt->stdin_append)
			write(1, inp->block, (size_t)inp->block_bytes);
		if ((t_uint)inp->block_bytes < inp->block_size)
		{
			finished = True;
			md_padding(inp);
		}
		sha256_block(inp, state);
	}
	if (!finished)  // (s)read failed
	{
		ft_memdel((void **)&state);
		return bad_read_error(inp->src->string);
	}
//	show_block(inp);
	output = sha_collect_digest(state);
	show_digest(opt, inp, "SHA256", output);
	sha_cleanup(&output, &state);
}

void	whirlpool_dispatch(t_options *opt, t_inp *inp)
{
	(void)opt;
	(void)inp;
}