/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:58:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/26 17:59:56 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_tools.h"

void		cleanup(t_line *in, t_options *opt, t_args *args)
{
	clean_t_line(&in);
	ft_memdel((void **)&opt);
	ft_memdel((void **)&args->op);
	ft_memdel((void **)&args);
}

/*
** @brief      Determines if the command entered is supported by the ft_ssl
**             library.
**
** @param      args  The arguments structure
**
** @return     TRUE if command is valud, FALSE otherwise.
*/

t_bool		is_valid_command(t_args *args)
{
	int	i;

	i = 0;
	while (g_implemented_commands[i].command_name)
		if (ft_strequ(args->command, g_implemented_commands[i++].command_name))
			return (TRUE);
	return (FALSE);
}

/*
** @brief      Invoke the routine that implements the command provided.
**
** @note       Before actually calling the appropriate routine, few preliminary
**             actions are carried out.
**             1) Parsing of the options (and exit, in cale of any error)
**             2) Input file reading to t_line structure
**             3) Asking for key and/or IV for DES family of algorithms
**
** @param      args  The arguments structure
*/

void		dispatch_arguments(t_args *args)
{
	t_options	*opt;
	int			i;
	t_line		*in;

	opt = parse_options(args);
	if (!(in = ft_read_fd_to_line(opt->fd_from, (t_bool)(!opt->encrypt &&
		(opt->base64 || ft_strequ(opt->command, "base64")))))->str)
	{
		cleanup(in, opt, args);
		return ;
	}
	ask_key_vector(opt);
	i = -1;
	while (g_implemented_commands[++i].command_name)
		if (ft_strequ(g_implemented_commands[i].command_name, args->command))
		{
			g_implemented_commands[i].f(opt, in, g_implemented_commands[i]);
			break ;
		}
	cleanup(in, opt, args);
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
	args->op = ac > 2 ? (char **)malloc(sizeof(char *) * (ac - 1)) : NULL;
	if (ac < 2)
		return (args);
	args->command = av[1];
	if (ac > 2)
	{
		i = 2;
		while (i < ac)
		{
			args->op[i - 2] = av[i];
			i++;
		}
		args->op[i - 2] = NULL;
	}
	return (args);
}
