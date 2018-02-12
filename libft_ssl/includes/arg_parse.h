/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:01:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 15:29:56 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_PARSE_H
# define ARG_PARSE_H

# include "libft.h"
# include "structures.h"
# include "ft_ssl.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>  // Don't forget to remove



char				*validate_hex(char *nbr, char *type);
unsigned long long	parse_hex(char *nbr);

t_args	*arg_parse(int ac, char **av);
t_bool	is_valid_command(t_args *args);
int		display_usage(t_args *args);
void	display_options_and_exit(char *option);
void	handle_file(int *fd, char *filename, t_bool from);
void	dispatch(t_args *args);


#endif