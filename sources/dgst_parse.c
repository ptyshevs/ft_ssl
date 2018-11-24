/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dgst_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:06:17 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/23 22:06:40 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures.h"
#include "ft_str.h"
#include "tools.h"
#include "md5.h"

static t_bool		dgst_core_flags(t_options *opt, char **options, int *i)
{
	static t_bool	p_met;

	if (ft_strequ(options[*i], "-p") && !p_met)
	{
		add_inp_src(&opt->inp_srcs, "", 0, True);
		opt->stdin_append = True;
		return ((p_met = True));
	}
	else if (ft_strequ(options[*i], "-p"))
	{
		add_inp_src(&opt->inp_srcs, "", -2, True);
		return ((opt->stdin_append = True));
	}
	else if (ft_strequ(options[*i], "-q"))
		return ((opt->quiet = True));
	else if (ft_strequ(options[*i], "-r"))
		return ((opt->reverse = True));
	return (False);
}

/*
** Final settings configuration before returning options to caller
**
** 1) If no input source found, add stdin
** 2) If `-q` specified, it overrides `-r` flag
*/

static t_options	*dgst_opt_finalize(t_options *opt)
{
	if (!opt->inp_srcs)
		add_inp_src(&opt->inp_srcs, "stdin", 0, True);
	if (opt->quiet)
		opt->reverse = False;
	return (opt);
}

t_options			*dgst_parse_opt(t_options *opt, char **options)
{
	static int		i = -1;
	static t_bool	file_met;

	if (!options)
	{
		add_inp_src(&opt->inp_srcs, "", 0, True);
		return (opt);
	}
	while (options[++i])
	{
		if (file_met)
			add_inp_src(&opt->inp_srcs, options[i], -1, True);
		else if (dgst_core_flags(opt, options, &i))
			continue ;
		else if (ft_strequ(options[i], "-s") && !options[i + 1])
			md5_invalid_opt(options[i]);
		else if (ft_strequ(options[i], "-s"))
			add_inp_src(&opt->inp_srcs, options[i++ + 1], -2, False);
		else
		{
			add_inp_src(&opt->inp_srcs, options[i], -1, True);
			file_met = True;
		}
	}
	return (dgst_opt_finalize(opt));
}
