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
#include <ft_tell.h>
#include <ft_printf.h>
#include "arg_tools.h"

/*
 * Initialize input structure, store block size and read first block
 */

t_inp		*init_input(int fd_from, int fd_to, t_command *command)
{
	t_inp	*inp;

	inp = ft_memalloc(sizeof(t_inp));
	inp->fd_from = fd_from;
	inp->fd_to = fd_to;
	inp->block_size = command->block_size;
	inp->block = ft_memalloc(sizeof(t_uc) * inp->block_size);
	inp->block_bytes = (t_uint)read(fd_from, inp->block, inp->block_size);
	if (inp->block_bytes == -1)
		ft_panic(1, "Failed to read from the stream provided for input\n");
	inp->bytes_total += inp->block_bytes;
	return (inp);
}

t_command	*map_command(char *command)
{
	int		i;

	i = 0;
	while (g_commands[i].command_name)
	{
		if (ft_strequ(g_commands[i].command_name, command))
			return (&g_commands[i]);
		i++;
	}
	return (NULL);
}

t_options	*cipher_parse_opt(t_options *opt, char **options)
{
	return (NULL);
}

void	md5_usage(void)
{
	ft_printf("usage: md5 [-pqr] [-s string] [files ...]\n");
}

void	md5_invalid_opt(char *option)
{
	ft_printf("md5: option requires an argument -- s\n");
	md5_usage();
	exit(1);
}

void	add_inp_src(t_list **inp_sources, char *str, int fd, t_bool is_stream)
{
	t_inp_src	*src;

	src = ft_memalloc(sizeof(t_inp_src));
	src->fd = fd;
	src->string = str;
	src->is_stream = is_stream;
	if (fd == -1 && is_stream)
		src->fd = open(str, O_RDONLY);
	ft_lstappend(inp_sources, ft_lstnew(src, sizeof(t_inp_src)));
}

t_options	*dgst_parse_opt(t_options *opt, char **options)
{
	int		i;

	i = 0;
	add_inp_src(&opt->inp_srcs, "stdin", 0, True);
	while (options[i])
	{
		if (ft_strequ(options[i], "-p"))
			opt->stdin_append = True;
		else if (ft_strequ(options[i], "-q"))
			opt->quiet = True;
		else if (ft_strequ(options[i], "-r"))
			opt->reverse = True;
		else if (ft_strequ(options[i], "-s"))
		{
			if (!options[i + 1])
				md5_invalid_opt(options[i]);
			add_inp_src(&opt->inp_srcs, options[i++ + 1], -1, False);
		}
		else
			add_inp_src(&opt->inp_srcs, options[i], -1, True);
		i++;
	}
	if (opt->quiet)  // overrides reverse
		opt->reverse = False;
	return (opt);
}

t_options	*parse_opt(t_cmd_type type, char **options)
{
	t_options	*opt;

	opt = ft_memalloc(sizeof(t_options));
	if (type == HASH)
		return dgst_parse_opt(opt, options);
	else if (type == CIPHER)
		return cipher_parse_opt(opt, options);
	else
		ft_panic(1, "Unrecognized command type\n");
	return (NULL);
}

void	show_inp_sources(t_list *inp_srcs)
{
	t_inp_src	*src;

	while (inp_srcs)
	{
		src = (t_inp_src *)inp_srcs->content;
		ft_printf("%10s [fd: %d | stream: %d]\n",
				src->string, src->fd, src->is_stream);
		inp_srcs = inp_srcs->next;
	}
}

int		main(int ac, char **av)
{
	t_args		*args;
	t_options	*opt;
	t_inp		*inp;
	t_command	*command;

	args = arg_parse(ac, av);
	if ((command = map_command(args->command)))
	{
		opt = parse_opt(command->type, args->op);
		show_inp_sources(opt->inp_srcs);

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
