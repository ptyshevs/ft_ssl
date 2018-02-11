/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:01:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/11 22:57:58 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_PARSE_H
# define ARG_PARSE_H

# include "libft.h"
# include "ft_ssl.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>  // Don't forget to remove

typedef struct	s_args
{
	char		*command;
	char		**options;
}				t_args;

typedef struct s_command
{
	char	*command_name;
	int 	(*f)(char **);
}				t_command;

typedef struct	s_options
{
	int			fd_to;
	int			fd_from;
	unsigned long long	key; // des key in hex
	unsigned long long	iv; // initial vector for des-cbc
	t_bool		base64;
	t_bool		encrypt;
}				t_options;

static t_command implemented_commands[] = {{"base64", &base64},
									{"des", &des_ecb},
									{"des-ecb", &des_ecb},
									{"des-cbc", &des_cbc},
									{NULL, NULL}};

char				*validate_hex(char *nbr, char *type);
unsigned long long	parse_hex(char *nbr);

t_args	*arg_parse(int ac, char **av);
t_bool	is_valid_command(t_args *args);
int		display_usage(t_args *args);
void	display_options_and_exit(char *option);
void	handle_file(int *fd, char *filename);

void	dispatch(t_args *args);


#endif