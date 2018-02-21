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

void	des3_ecb_encrypt(t_line *in, t_line *out, t_ull *keys)
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
		block = des_ecb_encrypt_block(keys, block);
		block_to_str(block, out, i, FALSE);
		i += 8;
	}
	block = add_padding(in->str + i, 8 + len == 0 ? 8 : -len);
	block_to_str(des_ecb_encrypt_block(keys, block), out, i, FALSE);
}

void	des3_ecb_decrypt(t_line *in, t_line *out, t_ull *keys)
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
		block = des_ecb_encrypt_block(keys, block);
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

int		des3_ecb(t_options *options, t_line *in)
{
	t_ull	keys[3][16];
	t_line	*out;
	t_line	*tmp;

	if (!in->str)
		return (1);
	out = init_line();
	options->key = pad_key(options->key, 48);
	get_subkeys(keys[0], parse_hex(ft_strsub(options->key, 0, 16)) , options->encrypt);
	get_subkeys(keys[1], parse_hex(ft_strsub(options->key, 16, 16)) , (t_bool) !options->encrypt);
	get_subkeys(keys[2], parse_hex(ft_strsub(options->key, 32, 16)) , options->encrypt);
	ft_strdel(&options->key);
	if (options->base64 && !options->encrypt)
	{
		base64_decrypt(in, (tmp = init_line()));
		ft_tline_replace(in, tmp);
		clean_t_line(&tmp);
	}
	options->encrypt ? des3_ecb_encrypt(in, out, keys[0]) :
	des3_ecb_decrypt(in, out, keys[0]);
	out_des(options, out);
	clean_t_line(&out);
	return (1);
}
