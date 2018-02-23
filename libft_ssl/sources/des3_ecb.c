/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_ecb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 21:16:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 13:50:21 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** @brief      Encrypt block using DES-EDE-ECB mode
**
**             Scheme goes as follows:
**             block = Encrypt(K3, Decrypt(K2, Encrypt(K1, block)))
**
** @param      block    The block
** @param      options  The options
**
** @return     Encrypted block
*/

t_ull	des3_ecb_encrypt_block(t_ull block, t_options *options)
{
	t_ull **subkeys;

	subkeys = (t_ull **)options->subkeys;
	block = des_encrypt_block(subkeys[0], block);
	block = des_encrypt_block(subkeys[1], block);
	block = des_encrypt_block(subkeys[2], block);
	return (block);
}

/*
** @brief      Decrypt block using DES-EDE-ECB mode
**
**             Scheme:
**             block = Decrypt(K3, Encrypt(K2, Decrypt(K1, block)))
**
** @param      block    The block
** @param      options  The options
**
** @return     Decrypted block
*/

t_ull	des3_ecb_decrypt_block(t_ull block, t_options *options)
{
	t_ull **subkeys;

	subkeys = (t_ull **)options->subkeys;
	block = des_encrypt_block(subkeys[2], block);
	block = des_encrypt_block(subkeys[1], block);
	block = des_encrypt_block(subkeys[0], block);
	return (block);
}

/*
** @brief      Create 3 arrays of size 16 from the 196-bit key
**
**             Key is padded from the left side with zeroes, and then splitted
**             in three 16-bytes keys. From each key, 16 subkeys are generated,
**             either in direct or reversed order (whether encrypt or decrypt).
**             If -p flag specified, key and/or IV displayed.
**             Key string is deleted after that.
**
** @param      opt   The option
*/

void	des3_create_subkeys(t_options *opt)
{
	t_ull	**sk;

	sk = (t_ull **)ft_memalloc(sizeof(t_ull *) * 3);
	sk[0] = (t_ull *)ft_memalloc(sizeof(t_ull) * 16);
	sk[1] = (t_ull *)ft_memalloc(sizeof(t_ull) * 16);
	sk[2] = (t_ull *)ft_memalloc(sizeof(t_ull) * 16);
	opt->key = pad_key(opt->key, 48);
	get_subkeys(sk[0], parse_hex(ft_strsub(opt->key, 0, 16)), opt->encrypt);
	get_subkeys(sk[1], parse_hex(ft_strsub(opt->key, 16, 16)), !opt->encrypt);
	get_subkeys(sk[2], parse_hex(ft_strsub(opt->key, 32, 16)), opt->encrypt);
	opt->subkeys = sk;
	if (opt->print_key_iv)
		display_key_iv(opt);
	ft_strdel(&opt->key);
}

/*
** @brief      Delete array of subkeys[3][16].
**
** @param      opt   The option
*/

void	des3_clean_subkeys(t_options *opt)
{
	t_ull	**sk;

	sk = (t_ull **)opt->subkeys;
	ft_memdel((void **)&(sk[0]));
	ft_memdel((void **)&(sk[1]));
	ft_memdel((void **)&(sk[2]));
	ft_memdel((void **)&(sk));
}
