/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:14:24 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/11 17:40:37 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include <stdio.h>  // Don't forget to remove

int		base64(char **options);
int 	des_ecb(char **options);
int 	des_cbc(char **options);

char	*base64_encode(char *plaintext);
char	*base64_decode(char *ciphertext);

char	*des_ecb_encode(char *plaintext);
char	*des_ecb_decode(char *ciphertext);

char	*des_cbc_encode(char *plaintext);
char	*des_cbc_decode(char *ciphertext);

#endif