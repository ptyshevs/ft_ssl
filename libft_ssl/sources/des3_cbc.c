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

/*
** @brief      DES (Data Encryption Standard) symmetric-key block cipher
**
** @param      options  The options
**
** @return     1 if everything okay, anything else otherwise
*/

int		des3_cbc(t_options *options, t_line *in)
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
	options->encrypt ? des_encrypt(in, out, options, des3_cbc_encrypt_block) :
						des_decrypt(in, out, options, des3_cbc_decrypt_block);
	out_des(options, out);
	des3_clean_subkeys(options);
	clean_t_line(&out);
	return (1);
}
