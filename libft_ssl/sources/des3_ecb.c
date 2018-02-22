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

t_ull	des3_ecb_encrypt_block(t_ull block, void *keys)
{
	t_ull **subkeys;

	subkeys = (t_ull **)keys;
	block = des_ecrypt_block(subkeys[0], block);
	block = des_ecrypt_block(subkeys[1], block);
	block = des_ecrypt_block(subkeys[2], block);
	return (block);
}

t_ull	des3_ecb_decrypt_block(t_ull block, void *keys)
{
	t_ull **subkeys;

	subkeys = (t_ull **)keys;
	block = des_ecrypt_block(subkeys[2], block);
	block = des_ecrypt_block(subkeys[1], block);
	block = des_ecrypt_block(subkeys[0], block);
	return (block);
}

void	des_encrypt(t_line *in, t_line *out, void *keys, t_mode mode)
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
		block = mode(block, keys);
		block_to_str(block, out, i, FALSE);
		i += 8;
	}
	block = add_padding(in->str + i, 8 + len == 0 ? 8 : -len);
	block_to_str(mode(block, keys), out, i, FALSE);
}

void	des_decrypt(t_line *in, t_line *out, void *keys, t_mode mode)
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
		block = mode(block, keys);
		block_to_str(block, out, (int)i, FALSE);
		i += 8;
	}
	out->len = i - out->str[i - 1];
}

t_ull	**des3_parse_subkeys(t_options *opt)
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
	return (sk);
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
	void	*keys;
	t_line	*out;
	t_line	*tmp;

	if (!in->str)
		return (1);
	out = init_line();
	keys = des3_parse_subkeys(options);
	if (options->base64 && !options->encrypt)
	{
		base64_decrypt(in, (tmp = init_line()));
		ft_tline_replace(in, tmp);
		clean_t_line(&tmp);
	}
	options->encrypt ? des_encrypt(in, out, keys, des3_ecb_encrypt_block) :
						des_decrypt(in, out, keys, des3_ecb_decrypt_block);
	out_des(options, out);
	des3_clean_subkeys(&keys);
	clean_t_line(&out);
	return (1);
}
