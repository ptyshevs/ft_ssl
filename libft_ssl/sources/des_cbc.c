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

#include "ft_ssl.h"

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
	!options->key_provided ? read_key(options) : 0;
	!options->iv_provided ? read_iv(options) : 0;
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
