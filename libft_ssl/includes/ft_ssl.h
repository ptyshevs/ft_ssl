/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:14:24 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 09:16:30 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "structures.h"
# include "libft.h"
# include <stdio.h>  // Don't forget to remove


int		base64(t_options *options);
int		des_ecb(t_options *options);
int		des_cbc(t_options *options);

char	*base64_encode(char *plaintext);
char	*base64_decode(char *ciphertext);

char	*des_ecb_encode(char *plaintext);
char	*des_ecb_decode(char *ciphertext);

char	*des_cbc_encode(char *plaintext);
char	*des_cbc_decode(char *ciphertext);

static t_command	g_implemented_commands[] = {
	{"base64", &base64},
	{"des", &des_ecb},
	{"des-ecb", &des_ecb},
	{"des-cbc", &des_cbc},
	{NULL, NULL}};

#endif
