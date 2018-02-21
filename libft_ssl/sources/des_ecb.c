/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:58:45 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 15:20:09 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"
#include "tools.h"

t_ull	des_ecb_encrypt_block(t_ull *keys, t_ull block)
{
	t_ull	left;
	t_ull	left_prev;
	t_ull	right;
	t_ull	right_prev;
	int		i;

	block = init_permut(block);
	i = 0;
	left = split_block(block, TRUE);
	left_prev = left;
	right = split_block(block, FALSE);
	right_prev = right;
	while (i < 16)
	{
		left = right;
		right = left_prev ^ apply_key(right_prev, keys[i]);
		left_prev = left;
		right_prev = right;
		i++;
	}
	block = final_permut((right << 32) | left);
	return (block);
}

t_ull	add_padding(t_uc *remainder, long long value)
{
	t_ull	block;
	int		i;

	block = 0;
	i = 8;
	while (i > value)
	{
		block = (block << 8) | *remainder++;
		i--;
	}
	i = 0;
	while (i++ < value)
		block = (block << 8) | value;
	return (block);
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
		block = des_ecb_encrypt_block(keys, block);
		block_to_str(block, out, i, FALSE);
		i += 8;
	}
	block = add_padding(in->str + i, 8 + len == 0 ? 8 : -len);
	block_to_str(des_ecb_encrypt_block(keys, block), out, i, FALSE);
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

int		des_ecb(t_options *options, t_line *in)
{
	t_ull	keys[16];
	t_line	*out;
	t_line	*tmp;

	if (!in->str)
		return (1);
	out = init_line();
	if (!options->key_provided)
		read_key(options);
	get_subkeys(keys, options->key, options->encrypt);
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
