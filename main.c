/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:12:18 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 12:08:33 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_str.h>
#include "arg_tools.h"

int		main(int ac, char **av)
{
	t_args		*args;
	t_options	*opt;
	t_line		*in;

	args = arg_parse(ac, av);
	if (is_valid_command(args))
	{
		opt = parse_options(args);
		in = ft_read_fd_to_line(opt->fd_from, (t_bool)(!opt->encrypt &&
		(opt->base64 || ft_strequ(opt->command, "base64"))));
		opt->debug = True; // change to False when deployed in production
		if (in->str)
			dispatch_arguments(in, opt);
		cleanup(in, opt, args);
	}
	else
		return (display_usage(args));
	return (0);
}
