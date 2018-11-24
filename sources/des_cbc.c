/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 16:14:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 15:20:18 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** @brief      Encrypt block using single DES in CBC mode
**
** @param      block    The 64-bit block
** @param      options  The options
**
** @return     DES-ECB encrypted block
*/

t_ull	des_cbc_encrypt_block(t_ull block, t_options *options)
{
	t_ull	res;

	res = des_encrypt_block((t_ull *)options->subkeys, block ^ options->iv);
	options->iv = res;
	return (res);
}

/*
** @brief      Decrypt block using single DES in CBC mode
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

t_ull	des_cbc_decrypt_block(t_ull block, t_options *options)
{
	t_ull	res;

	res = des_encrypt_block((t_ull *)options->subkeys, block) ^ options->iv;
	options->iv = block;
	return (res);
}
