/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:58:45 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/13 22:44:43 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "tools.h"
#include <fcntl.h>

void	initial_permutation(t_block *block)
{
	int	i;
	// int	bit;

	i = 0;
	while (i < 64)
	{
		// bit1 = block->b & (1 << g_init_permut[i]);
		int bit2 = *block & (1 << (64 - i));
		ft_printf("current bit is %d\n", bit2);
		i++;
	}
}

char	*des_ecb_encrypt(t_options *options, char *in)
{
	t_block block;

	while (*in)
	{
		block = *in;
	}
	(void)options;
	(void)in;
	return (NULL);
}

char	*des_ecb_decrypt(t_options *options, char *in)
{
	(void)options;
	(void)in;
	return (NULL);
}

/*
** @brief      DES (Data Encryption Standard) symmetric-key block cipher
**
** @param      options  The options
**
** @return     1 if everything okay, anything else otherwise
*/

int		des_ecb(t_options *options)
{
	char	*in;
	char	*out;

	in = read_fd(options->fd_from);
	if (!options->key_provided)
		read_key(options);
	ft_printf("key: %064llb\n", options->key);
	out = options->encrypt ?	des_ecb_encrypt(options, in) :
								des_ecb_decrypt(options, in);
	if (out)
		ft_dprintf(options->fd_to, "%s", out);
	free(out);
	return (1);
}
