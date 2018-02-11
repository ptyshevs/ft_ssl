/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:01:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/11 17:41:42 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_PARSE_H
# define ARG_PARSE_H

# include "libft.h"
# include "ft_ssl.h"
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
	int			key; // des key in hex
	int			initial_vector; // initial vector for des-cbc
	t_bool		encode;

}				t_options;

static t_command implemented_commands[] = {{"base64", &base64},
									{"des", &des_ecb},
									{"des-ecb", &des_ecb},
									{"des-cbc", &des_cbc},
									{NULL, NULL}};


t_args	*arg_parse(int ac, char **av);
t_bool	is_valid_command(t_args *args);
void	show_usage(t_args *args);
void	dispatch(t_args *args);


#endif