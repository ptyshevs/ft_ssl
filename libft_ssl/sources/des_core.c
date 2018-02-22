/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:18:12 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/22 17:18:25 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "permutations.h"
#include "ft_ssl.h"

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
