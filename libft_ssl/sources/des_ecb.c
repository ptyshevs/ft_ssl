/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:58:45 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/22 21:26:36 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"
#include "tools.h"

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

void	des_clean_subkeys(t_options *opt)
{
	ft_memdel(&opt->subkeys);
}

void	des_ecb_encrypt(t_line *in, t_line *out, t_ull *keys)
{
	long long	len;
	int			i;
	t_ull		block;

	len = (long long)in->len;
	out->len = (size_t)(len + (len % 8 == 0 ? 8 : 8 - (len % 8)));
	out->str = ft_memalloc(out->len);
	i = 0;
	while ((len -= 8) >= 0)
	{
		block = str_to_block(in->str + i);
		block = des_encrypt_block(keys, block);
		block_to_str(block, out, i, FALSE);
		i += 8;
	}
	block = add_padding(in->str + i, 8 + len == 0 ? 8 : -len);
	block_to_str(des_encrypt_block(keys, block), out, i, FALSE);
}

void	des_ecb_decrypt(t_line *in, t_line *out, t_ull *keys)
{
	long long	len;
	t_ull		i;
	t_ull		block;

	len = (long long)in->len;
	out->str = ft_memalloc(in->len);
	i = 0;
	while ((len -= 8) >= 0)
	{
		block = str_to_block(in->str + i);
		block = des_encrypt_block(keys, block);
		block_to_str(block, out, (int)i, FALSE);
		i += 8;
	}
	out->len = i - out->str[i - 1];
}

/*
** @brief      DES (Data Encryption Standard) symmetric-key block cipher
**
** @param      options  The options
**
** @return     1 if everything okay, anything else otherwise
*/

int		des_ecb(t_options *options, t_line *in)
{
	t_ull	keys[16];
	t_line	*out;
	t_line	*tmp;

	if (!in->str)
		return (1);
	out = init_line();
	get_subkeys(keys, parse_hex(pad_key(options->key, 16)) , options->encrypt);
	if (options->base64 && !options->encrypt)
	{
		base64_decrypt(in, (tmp = init_line()));
		ft_tline_replace(in, tmp);
		clean_t_line(&tmp);
	}
	options->encrypt ? des_ecb_encrypt(in, out, keys) :
						des_ecb_decrypt(in, out, keys);
	out_des(options, out);
	clean_t_line(&out);
	return (1);
}
