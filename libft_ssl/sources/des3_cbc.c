/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_cbc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 21:16:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 13:03:58 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** @brief      Encrypt block using DES-EDE-CBC mode
**
** @note       Encryption is going as follows: first, we ask for 192-bit key,
**             which, excluding parity bits, provides us with 168-bit effective
**             key size. Key is then split into three 64-bit keys.
**
**             Each block then encrypted using the following scheme:
**
**             block = Encrypt(K1, block XOR IV)
**             block = Decrypt(K2, block) XOR IV
**             block = Encrypt(K3, block XOR IV),
**             where IV is either an Initializing Vector, or the previous block
**
** @param      block    The block
** @param      options  The options
**
** @return     Encrypted block
*/

t_ull	des3_cbc_encrypt_block(t_ull block, t_options *options)
{
	t_ull			**subkeys;
	t_ull			res;

	subkeys = (t_ull **)options->subkeys;
	res = des_encrypt_block(subkeys[0], block ^ options->iv);
	res = des_encrypt_block(subkeys[1], res) ^ options->iv;
	res = des_encrypt_block(subkeys[2], res ^ options->iv);
	options->iv = res;
	return (res);
}

/*
** @brief      Decrypt block using DES-EDE-CBC mode
**
** @note       The decryption flow of Triple DES is the exact reverse of the
**             encryption:
**
**             block = Decrypt(K3, block) XOR IV
**             block = Encrypt(K2, block XOR IV)
**             block = Decrypt(K1, block) XOR IV,
**             where IV is either an Initializing Vector, or the previous block
**
** @param      block    The block
** @param      options  The options
**
** @return     Decrypted block
*/

t_ull	des3_cbc_decrypt_block(t_ull block, t_options *options)
{
	t_ull	**subkeys;
	t_ull	res;

	subkeys = (t_ull **)options->subkeys;
	res = des_encrypt_block(subkeys[2], block) ^ options->iv;
	res = des_encrypt_block(subkeys[1], res ^ options->iv);
	res = des_encrypt_block(subkeys[0], res) ^ options->iv;
	options->iv = block;
	return (res);
}
