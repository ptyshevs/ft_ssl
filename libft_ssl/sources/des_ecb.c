/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:58:45 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 15:12:07 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** @brief      Encrypt block using single DES in ECB mode
**
** @param      block    The 64-bit block
** @param      options  The options
**
** @return     DES-ECB encrypted block
*/

t_ull	des_ecb_encrypt_block(t_ull block, t_options *options)
{
	return (des_encrypt_block((t_ull *)options->subkeys, block));
}

/*
** @brief      Decrypt block using single DES in ECB mode
**
** @note       This function is identical to the encryption and differs only in
**             the context. For decryption, the order of subkeys stored in
**             <options->subkeys> is reversed.
**
** @param      block    The 64-bit block
** @param      options  The options
**
** @return     DES-ECB decrypted block
*/

t_ull	des_ecb_decrypt_block(t_ull block, t_options *options)
{
	return (des_encrypt_block((t_ull *)options->subkeys, block));
}

/*
** @brief      Create array of 16 subkeys from padded 16-bytes key,
**             and put it into opt->subkeys field. If -p flag specified, display
**             key and/or IV to the terminal.
**             Release memory allocated for opt->key during padding.
**
** @param      opt   The options
*/

void	des_create_subkeys(t_options *opt)
{
	t_ull	*sk;

	sk = ft_memalloc(sizeof(t_ull) * 16);
	opt->key = pad_key(opt->key, 16);
	get_subkeys(sk, parse_hex(ft_strsub(opt->key, 0, 16)), opt->encrypt);
	opt->subkeys = sk;
	if (opt->print_key_iv)
		display_key_iv(opt);
	ft_strdel(&opt->key);
}

/*
** @brief      Release resources allocated for storing 16 subkeys.
**
** @param      opt   The option
*/

void	des_clean_subkeys(t_options *opt)
{
	ft_memdel(&opt->subkeys);
}
