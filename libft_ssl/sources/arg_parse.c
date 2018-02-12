/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:58:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 08:12:39 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_parse.h"
#include "ft_ssl.h"

t_bool		is_valid_command(t_args *args)
{
	int	i;

	i = 0;
	while (g_implemented_commands[i].command_name)
		if (ft_strequ(args->command, g_implemented_commands[i++].command_name))
			return (TRUE);
	return (FALSE);
}

t_options	*init_options(void)
{
	t_options *opt;

	opt = (t_options *)malloc(sizeof(t_options));
	opt->fd_from = 0;
	opt->fd_to = 1;
	opt->base64 = FALSE;
	opt->encrypt = TRUE;
	opt->key = 0;
	opt->key_provided = FALSE;
	opt->iv = 0;
	opt->iv_provided = FALSE;
	return (opt);
}

t_options	*parse_options(t_args *args)
{
	t_options	*opt;

	opt = init_options();
	while (args->options && *args->options)
	{
		if (ft_strequ(*args->options, "-e") || ft_strequ(*args->options, "-d"))
			opt->encrypt = ft_strequ(*args->options, "-e") ? TRUE : FALSE;
		else if (ft_strequ(*args->options, "-a"))
			opt->base64 = TRUE;
		else if (ft_strequ(*args->options, "-i"))
			handle_file(&opt->fd_from, *(args->options++ + 1));
		else if (ft_strequ(*args->options, "-o"))
			handle_file(&opt->fd_to, *(args->options++ + 1));
		else if (ft_strequ(*args->options, "-k") && (opt->key_provided = TRUE))
			*(args->options + 1) == NULL ? display_options_and_exit(NULL) :
			(opt->key = parse_hex(validate_hex(*(args->options++ + 1), "key")));
		else if (ft_strequ(*args->options, "-v") && (opt->iv_provided = TRUE))
			*(args->options + 1) == NULL ? display_options_and_exit(NULL) :
			(opt->iv = parse_hex(validate_hex(*(args->options++ + 1), "iv")));
		else
			display_options_and_exit(*args->options);
		args->options++;
	}
	return (opt);
}

void		dispatch(t_args *args)
{
	t_options	*opt;
	char		**options_tmp;
	int			i;

	options_tmp = args->options;
	opt = parse_options(args);
	i = 0;
	while (g_implemented_commands[i].command_name)
	{
		if (ft_strequ(g_implemented_commands[i].command_name, args->command))
		{
			if (!g_implemented_commands[i].f(opt))
				ft_dprintf(2, "Something went wrong with %s encryption function\n", args->command);
			break ;
		}
		i++;
	}
	if (opt->fd_from != 0)
		close(opt->fd_from);
	if (opt->fd_to != 1)
		close(opt->fd_to);
	free(opt);
	free(options_tmp);
	free(args);
}

/*
** @brief      Parse command-line arguments into a structure
**
** @param      ac    Argument counter
** @param      av    Argument vector
**
** @return     Arguments DS (command + options)
*/

t_args		*arg_parse(int ac, char **av)
{
	t_args	*args;
	int		i;

	args = malloc(sizeof(t_args));
	args->command = NULL;
	args->options = ac > 2 ? (char **)malloc(sizeof(char *) * (ac - 1)) : NULL;
	if (ac < 2)
		return (args);
	args->command = av[1];
	if (ac > 2)
	{
		i = 2;
		while (i < ac)
		{
			args->options[i - 2] = av[i];
			i++;
		}
		args->options[i - 2] = NULL;
	}
	return (args);
}
