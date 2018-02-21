/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DES_tools_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:15:35 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/21 12:15:49 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_ull	split_block(t_ull block, t_bool left)
{
	return ((left ? block >> 32 : block) & 0xFFFFFFFF);
}

t_ull	str_to_block(t_uc *str)
{
	t_ull	block;
	int		i;

	block = 0;
	i = 0;
	while (i++ < 8)
		block = (block << 8) | *str++;
	return (block);
}

void	ask_key_vector(t_args *args, t_options *options)
{
	if (ft_strequ(args->command, "des-cbc") &&
		options->key_provided && !options->iv_provided)
		ft_message_and_exit("iv undefined", 2, 1);
	if (!ft_strequ(args->command, "base64"))
	{
		if (!options->key_provided)
			read_key(options);
		if (!options->iv_provided)
			read_iv(options);
	}
}