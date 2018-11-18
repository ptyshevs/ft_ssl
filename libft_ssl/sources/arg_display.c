/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 18:11:28 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 11:10:00 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_str.h>
#include "arg_tools.h"

/*
** @brief      Show usage in STDOUT
**
** @param      args  The arguments
**
** @return     1 (as return status back to main)
*/

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
		while (g_commands[i].command_name)
			ft_printf("%s\n", g_commands[i++].command_name);
		return (1);
	}
}

/*
** @brief      Display options to the terminal and exit with error status 1
**
** @param      option  The option
*/

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
				"-v\t\tiv in hex is the next argument\n"
				"-p\t\tprint key and iv (DES)\n");
	exit(1);
}

/*
** @brief      Display key and Initialization Vector, according to the -p flag.
**
** @param      options  The options
*/

void	display_key_iv(t_options *options)
{
	ft_printf("key=%s\n", options->key);
	if (ft_strequ(options->command, "des-cbc") ||
		ft_strequ(options->command, "des3-cbc"))
		ft_printf("iv =%llX\n", options->iv);
}

/*
** @brief      Handle input/output file opening
**
** @param      fd        Pointer to the location where to store FD in case of
**                       success.
** @param      filename  The filename
** @param      from      (t_bool) Is it file to read from (TRUE) or write to
**                       (FALSE)?
*/

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
