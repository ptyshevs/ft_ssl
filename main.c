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

#include "arg_tools.h"
#include "tools.h"

void	input_cleanup(t_inp **ainp)
{
	ft_memdel((void **)&(*ainp)->block);
	ft_memdel((void **)&(*ainp)->buffer);
	ft_memdel((void **)ainp);

}

void	apply_to_srcs(t_command *command, t_options *opt)
{
	t_list		*tmp;
	t_inp_src	*src;
	t_inp		*inp;

	tmp = opt->inp_srcs;
	while (tmp)
	{
		src = (t_inp_src *)tmp->content;
		inp = init_input(command, src);
		command->f(opt, inp);
		input_cleanup(&inp);
		tmp = tmp->next;
	}
}


int		main(int ac, char **av)
{
	t_args		*args;
	t_options	*opt;
	t_command	*command;

	args = arg_parse(ac, av);
	if ((command = map_command(args->command)))
	{
		opt = parse_opt(command->type, args->op);
		show_inp_sources(opt->inp_srcs);

		if (command->type == HASH)
			apply_to_srcs(command, opt);
//		in = ft_read_fd_to_line(opt->fd_from, (t_bool)(!opt->encrypt &&
//		(opt->base64 || ft_strequ(opt->command, "base64"))));
//		inp = init_input(opt->fd_from, opt->fd_to, command);
//		if (inp)
//			dispatch_arguments(in, opt);
//		cleanup(in, opt, args);
	}
	else
		return (display_usage(args));
	return (0);
}
