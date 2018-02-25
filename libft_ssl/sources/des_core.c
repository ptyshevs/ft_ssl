/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:18:12 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 15:08:00 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "permutations.h"
#include "ft_ssl.h"

/*
** @brief      Generic block encryption routine: given 16 subkeys, encode
**             64-bit block of data.
**
** @note       Algorithm steps:
**             1) apply Initial Permutation
**             2) split block in 32-bit Left and Right parts
**             3) For 16 iterations, we now:
**                a) record Right into Left variable
**                b) Right = Left XOR apply_key(right_prev, current_subkey)
**
** @param      keys   The subkeys array
** @param      block  The block
**
** @return     Encrypted block
*/

t_ull	des_encrypt_block(t_ull *keys, t_ull block)
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

/*
** @brief      Adds a padding to the last block
**
** @param      remainder  The remainder string
** @param      value      The value to pad with
**
** @return     The last padded string
*/

t_ull	add_padding(t_uc *remainder, long long value)
{
	t_ull	block;
	int		i;

	block = 0;
	i = 8;
	while (i-- > value)
		block = (block << 8) | *remainder++;
	while (i-- >= 0)
		block = (block << 8) | value;
	return (block);
}

/*
** @brief      Generic encryption routine
**
** @param      in       Input string
** @param      out      The output string
** @param      options  The options
** @param      mode     The mode of operation, routine to encrypt one block
*/

void	des_encrypt(t_line *in, t_line *out, t_options *options, t_mode mode)
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
		block = mode(block, options);
		block_to_str(block, out, i, FALSE);
		i += 8;
	}
	block = add_padding(in->str + i, 8 + len == 0 ? 8 : -len);
	block_to_str(mode(block, options), out, i, FALSE);
}

/*
** @brief      Generic decryption routine
**
** @param      in       Input string
** @param      out      The output string
** @param      options  The options
** @param      mode     The mode of operation, routine to decrypt one block
*/

void	des_decrypt(t_line *in, t_line *out, t_options *options, t_mode mode)
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
		block = mode(block, options);
		block_to_str(block, out, (int)i, FALSE);
		i += 8;
	}
	out->len = i - out->str[i - 1];
}

/*
** @brief      Use one of the commands fields to perform the specific DES algo
**
** @note       Command structure must have the following interface:
**
**             * command.create_subkeys(t_options *options) - fill in the
**             opt->subkeys field
**             * command.f_encrypt - routine to encrypt one block
**             * command.f_decrypt - routine to decrypt one block
**             * command.clean_subkeys - routine to free the resources allocated
**                 when creating subkeys array
**
** @param      opt      The option
** @param      in       Input string
** @param      command  The command structure
*/

void	des_map(t_options *opt, t_line *in, t_command command)
{
	t_line	*out;
	t_line	*tmp;

	if (!in->str)
		return ;
	out = init_line();
	command.create_subkeys(opt);
	if (opt->base64 && !opt->encrypt)
	{
		base64_decrypt(in, (tmp = init_line()));
		ft_tline_replace(in, tmp);
		clean_t_line(&tmp);
	}
	opt->encrypt ? des_encrypt(in, out, opt, command.f_encrypt) :
					des_decrypt(in, out, opt, command.f_decrypt);
	out_des(opt, out);
	command.clean_subkeys(opt);
	clean_t_line(&out);
}
