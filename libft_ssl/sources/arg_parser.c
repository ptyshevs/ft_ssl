/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:58:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 14:51:35 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_tools.h"

t_bool		is_valid_command(t_args *args)
{
	int	i;

	i = 0;
	while (g_implemented_commands[i].command_name)
		if (ft_strequ(args->command, g_implemented_commands[i++].command_name))
			return (TRUE);
	return (FALSE);
}

void		dispatch_arguments(t_args *args)
{
	t_options	*opt;
	int			i;
	t_line		*in;

	opt = parse_options(args);
	if (!(in = ft_read_fd_to_line(opt->fd_from, (t_bool) (!opt->encrypt && opt->base64)))->str)
	{
		clean_t_line(&in);
		free(opt);
		free(args);
		return ;
	}
	ask_key_vector(args, opt);
	i = -1;
	while (g_implemented_commands[++i].command_name)
		if (ft_strequ(g_implemented_commands[i].command_name, args->command))
		{
			if (!g_implemented_commands[i].f(opt, in))
				ft_dprintf(2, "Smth went wrong with %s encryption function\n",
					args->command);
			break ;
		}
	clean_t_line(&in);
	free(opt);
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
