/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:58:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/11 17:47:03 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_parse.h"
#include "ft_ssl.h"

t_bool	is_valid_command(t_args *args)
{
	int	i;

	i = 0;
	while (implemented_commands[i].command_name)
		if (ft_strequ(args->command, implemented_commands[i++].command_name))
			return (TRUE);
	return (FALSE);
}

void	show_usage(t_args *args)
{
	int	i;

	if (args->command == NULL)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", args->command);
	ft_printf("Standard commands:\n");
	ft_printf("\nMessage Digest commands:\n");
	ft_printf("\nCipher commands:\n");
	i = 0;
	while (implemented_commands[i].command_name)
		printf("%s\n", implemented_commands[i++].command_name);
	}
}

void	dispatch(t_args *args)
{
	(void)args;
	printf("dispatch was called\n");
}


int		validate(t_args *args)
{
	(void)args;
	return (0);
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
	int	i;

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