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
	char				*key;
	t_bool				key_provided;
	void				*subkeys;
	unsigned long long	iv;
	t_bool				iv_provided;
	t_bool				print_key_iv;
	t_bool				base64;
	t_bool				encrypt;
}				t_options;

typedef struct s_command
{
	char	*command_name;
	int		(*f)(t_options *opt, t_line *in);
}				t_command;

typedef unsigned long long	t_block;
typedef t_ull				(*t_mode)(t_ull block, t_options *options);

#endif
