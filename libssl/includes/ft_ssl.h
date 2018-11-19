/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:14:24 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 14:50:58 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "structures.h"
# include "libft.h"
# include "tools.h"

void	base64(t_options *options, t_line *in, t_command command);
void	base64_encrypt(t_line *in, t_line *out);
void	base64_decrypt(t_line *in, t_line *out);

void	des_encrypt(t_line *in, t_line *out, t_options *options, t_mode mode);
void	des_decrypt(t_line *in, t_line *out, t_options *options, t_mode mode);
void	des_map(t_options *opt, t_line *in, t_command command);
t_ull	des_encrypt_block(t_ull *keys, t_ull block);

t_ull	des_ecb_encrypt_block(t_ull block, t_options *options);
t_ull	des_ecb_decrypt_block(t_ull block, t_options *options);
t_ull	des_cbc_encrypt_block(t_ull block, t_options *options);
t_ull	des_cbc_decrypt_block(t_ull block, t_options *options);
void	des_create_subkeys(t_options *opt);
void	des_clean_subkeys(t_options *opt);

t_ull	des3_ecb_encrypt_block(t_ull block, t_options *options);
t_ull	des3_ecb_decrypt_block(t_ull block, t_options *options);
t_ull	des3_cbc_encrypt_block(t_ull block, t_options *options);
t_ull	des3_cbc_decrypt_block(t_ull block, t_options *options);
void	des3_create_subkeys(t_options *opt);
void	des3_clean_subkeys(t_options *options);

static t_command	g_commands[] = {
	{"base64", &base64, NULL, NULL, NULL, NULL},
	{"des", &des_map, des_ecb_encrypt_block, des_ecb_decrypt_block,
		des_create_subkeys, des_clean_subkeys},
	{"des-ecb", &des_map, des_ecb_encrypt_block, des_ecb_decrypt_block,
		des_create_subkeys, des_clean_subkeys},
	{"des-cbc", &des_map, des_cbc_encrypt_block, des_cbc_decrypt_block,
		des_create_subkeys, des_clean_subkeys},
	{"des3", &des_map, des3_ecb_encrypt_block, des3_ecb_decrypt_block,
		des3_create_subkeys, des3_clean_subkeys},
	{"des3-ecb", &des_map, des3_ecb_encrypt_block, des3_ecb_decrypt_block,
		des3_create_subkeys, des3_clean_subkeys},
	{"des3-cbc", &des_map, des3_cbc_encrypt_block, des3_cbc_decrypt_block,
		des3_create_subkeys, des3_clean_subkeys},
	{NULL, NULL, NULL, NULL, NULL, NULL}};

static	char	*g_options_provided[] = {
	"-e", "-d",
	"-i", "-o",
	"-k", "-v",
	"-a", "-p",
	NULL
};



// Message Digest commands and allowed options

#endif
