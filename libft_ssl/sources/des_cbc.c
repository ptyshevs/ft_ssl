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

#include "permutations.h"
#include "ft_ssl.h"

void	des_cbc_encrypt(t_line *in, t_line *out, t_ull *keys, t_ull iv)
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
		block = str_to_block(in->str + i) ^ iv;
		block = des_ecrypt_block(keys, block);
		iv = block;
		block_to_str(block, out, i, FALSE);
		i += 8;
	}
	block = add_padding(in->str + i, 8 + len == 0 ? 8 : -len) ^ iv;
	block_to_str(des_ecrypt_block(keys, block), out, i, FALSE);
}

void	des_cbc_decrypt(t_line *in, t_line *out, t_ull *keys, t_ull iv)
{
	long long	len;
	t_ull		i;
	t_ull		block;
	t_ull		prev_block;

	len = (long long)in->len;
	out->str = ft_memalloc(in->len);
	i = 0;
	while ((len -= 8) >= 0)
	{
		block = str_to_block(in->str + i);
		prev_block = block;
		block = des_ecrypt_block(keys, block) ^ iv;
		iv = prev_block;
		block_to_str(block, out, (int)i, FALSE);
		i += 8;
	}
	out->len = i - out->str[i - 1];
}

/*
** @brief      Data Encryption Standard cipher
**
** @param      options  The options
**
** @return     1 if everything is OK, otherwise 0
*/

int		des_cbc(t_options *options, t_line *in)
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
	options->encrypt ? des_cbc_encrypt(in, out, keys, options->iv) :
						des_cbc_decrypt(in, out, keys, options->iv);
	out_des(options, out);
	clean_t_line(&out);
	return (1);
}
