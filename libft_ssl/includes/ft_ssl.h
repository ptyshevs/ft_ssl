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
# include <stdio.h>  // Don't forget to remove


int		base64(t_options *options, t_line *in);
int		des_ecb(t_options *options, t_line *in);
int		des_cbc(t_options *options, t_line *in);
int		des3_ecb(t_options *options, t_line *in);
int		des3_cbc(t_options *options, t_line *in);

void	base64_encrypt(t_line *in, t_line *out);
void	base64_decrypt(t_line *in, t_line *out);

void	des_encrypt(t_line *in, t_line *out, t_options *options, t_mode mode);
void	des_decrypt(t_line *in, t_line *out, t_options *options, t_mode mode);
void	des3_create_subkeys(t_options *opt);
void	des3_clean_subkeys(void **ask);


t_ull	des_encrypt_block(t_ull *keys, t_ull block);
void	des_ecb_encrypt(t_line *in, t_line *out, t_ull *keys);
void	des_ecb_decrypt(t_line *in, t_line *out, t_ull *keys);

char	*des_cbc_encode(char *plaintext);
char	*des_cbc_decode(char *ciphertext);

static t_command	g_implemented_commands[] = {
	{"base64", &base64},
	{"des", &des_ecb},
	{"des-ecb", &des_ecb},
	{"des-cbc", &des_cbc},
	{"des3", &des3_cbc},
	{"des3-ecb", &des3_ecb},
	{"des3-cbc", &des3_cbc},
	{NULL, NULL}};

#endif
