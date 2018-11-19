/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 07:56:00 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 13:00:00 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

#include <ft_gnls.h>
# include "libft.h"

typedef unsigned long long	t_block; // for what?

typedef struct	s_args
{
	char		*command;
	char		**op;
}				t_args;

typedef struct	s_options
{
	int					fd_to;
	int					fd_from;
	char				*key;
	t_bool				key_provided;
	void				*subkeys;
	unsigned long long	iv;
	t_bool				iv_provided;
	t_bool				print_key_iv;
	t_bool				base64;
	t_bool				encrypt;
	t_bool				debug;
	char				*command;
}				t_options;

typedef t_ull				(*t_mode)(t_ull block, t_options *options);

typedef struct	s_command
{
	char	*command_name;
	void	(*f)(t_options *opt, t_line *in, struct s_command);
	t_mode	f_encrypt;
	t_mode	f_decrypt;
	void	(*create_subkeys)(t_options *options);
	void	(*clean_subkeys)(t_options *options);
}				t_command;

#endif