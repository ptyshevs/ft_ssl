/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 18:11:28 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 21:32:50 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_tools.h"

int		display_usage(t_args *args)
{
	int	i;

	if (args->command == NULL)
	{
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		return (0);
	}
	else
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n",
			args->command);
		ft_printf("Standard commands:\n");
		ft_printf("\nMessage Digest commands:\n");
		ft_printf("\nCipher commands:\n");
		i = 0;
		while (g_implemented_commands[i].command_name)
			ft_printf("%s\n", g_implemented_commands[i++].command_name);
		return (1);
	}
}

void	display_options_and_exit(char *option)
{
	if (option != NULL)
		ft_printf("unknown option '%s'\n", option);
	ft_printf("options are\n");
	ft_printf("-i <file>\tinput file\n-o <file>\toutput file\n"
				"-e\t\tencrypt\n"
				"-d\t\tdecrypt\n"
				"-a\t\tbase64 encode/decode, depending on encryption flag\n"
				"-k\t\tkey in hex is the next argument\n"
				"-v\t\tiv in hex is the next argument\n");
	exit(1);
}

void	handle_file(int *fd, char *filename, t_bool from)
{
	if (from && filename == NULL)
		display_options_and_exit(NULL);
	else if (from && (*fd = open(filename, O_RDONLY)) == -1)
	{
		perror(filename);
		exit(1);
	}
	else if ((*fd = open(filename, O_RDWR | O_CREAT, 0664)) == -1)
	{
		perror(filename);
		exit(1);
	}
}
