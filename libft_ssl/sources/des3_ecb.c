/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 21:16:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/21 21:17:28 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"
#include "tools.h"

t_ull	des3_ecb_encrypt_block(t_ull block, t_options *options)
{
	t_ull **subkeys;

	subkeys = (t_ull **)options->subkeys;
	block = des_encrypt_block(subkeys[0], block);
	block = des_encrypt_block(subkeys[1], block);
	block = des_encrypt_block(subkeys[2], block);
	return (block);
}

t_ull	des3_ecb_decrypt_block(t_ull block, t_options *options)
{
	t_ull **subkeys;

	subkeys = (t_ull **)options->subkeys;
	block = des_encrypt_block(subkeys[2], block);
	block = des_encrypt_block(subkeys[1], block);
	block = des_encrypt_block(subkeys[0], block);
	return (block);
}

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
	ft_strdel(&opt->key);
	opt->subkeys = sk;
}

void	des3_clean_subkeys(void **ask)
{
	t_ull	**sk;

	sk = (t_ull **)*ask;
	free(sk[0]);
	free(sk[1]);
	free(sk[2]);
	free(sk);
}

/*
** @brief      DES (Data Encryption Standard) symmetric-key block cipher
**
** @param      options  The options
**
** @return     1 if everything okay, anything else otherwise
*/

int		des3_ecb(t_options *options, t_line *in)
{
	t_line	*out;
	t_line	*tmp;

	if (!in->str)
		return (1);
	out = init_line();
	des3_create_subkeys(options);
	if (options->base64 && !options->encrypt)
	{
		base64_decrypt(in, (tmp = init_line()));
		ft_tline_replace(in, tmp);
		clean_t_line(&tmp);
	}
	options->encrypt ? des_encrypt(in, out, options, des3_ecb_encrypt_block) :
						des_decrypt(in, out, options, des3_ecb_decrypt_block);
	out_des(options, out);
	des3_clean_subkeys(&options->subkeys);
	clean_t_line(&out);
	return (1);
}
