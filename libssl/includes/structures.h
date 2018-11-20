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
#include <ft_lst.h>
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
	char				*command;
	// Cipher options
	char				*key;
	t_bool				key_provided;
	void				*subkeys;
	unsigned long long	iv;
	t_bool				iv_provided;
	t_bool				print_key_iv;
	t_bool				base64;
	t_bool				encrypt;
	// Digests options
	t_list				*inp_srcs;
	t_bool				stdin_append;
	t_bool				quiet;
	t_bool				reverse;
}				t_options;

typedef t_ull				(*t_mode)(t_ull block, t_options *options);

//typedef struct	s_cipher
//{
//	char	*command_name;
//	void	(*f)(t_options *opt, t_line *in, struct s_cipher);
//	t_mode	f_encrypt;
//	t_mode	f_decrypt;
//	void	(*create_subkeys)(t_options *options);
//	void	(*clean_subkeys)(t_options *options);
//}				t_cipher;

/*
** Structure for orchestrating streaming
*/

typedef struct	s_inp
{
	int			fd_to;
	int			fd_from;
	t_uint		block_size;  // size of the block
	t_uc		*block;
	t_ull		bytes_total;  // total # of bytes read
	t_ull		bits_total;
	int			block_bytes;  // returned by read/read_string
	t_uc		*buffer;
}				t_inp;

typedef enum	e_cmd_type
{
	NONE,
	HASH,
	CIPHER
}				t_cmd_type;

typedef struct	s_command
{
	char		*command_name;
	t_cmd_type	type;
	void		(*f)(t_options *opt, t_inp *inp);
	t_uint		block_size;
}				t_command;

typedef struct	s_inp_src
{
	// name of a file if source is stream, otherwise string contains the message
	char		*string;
	int			fd;
	t_bool		is_stream;
}				t_inp_src;

#endif
