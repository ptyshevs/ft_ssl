/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 07:56:00 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/14 11:51:11 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"

typedef struct	s_args
{
	char		*command;
	char		**options;
}				t_args;

typedef struct	s_options
{
	int					fd_to;
	int					fd_from;
	unsigned long long	key; // des key in hex
	t_bool				key_provided;
	unsigned long long	iv; // initial vector for des-cbc
	t_bool				iv_provided;
	t_bool				base64;
	t_bool				encrypt;
}				t_options;

typedef struct s_command
{
	char	*command_name;
	int		(*f)(t_options *opt);
}				t_command;

typedef unsigned long long	t_block;

#endif
