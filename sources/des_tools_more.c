/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_tools_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:15:35 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 15:42:01 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>
#include <ft_str.h>
#include <ft_tell.h>
#include "ft_ssl.h"

/*
** @brief      Splits a 64-bit block into two 32-bit halves.
**
** @param      block  The block
** @param      left   TRUE if it is a left part, FALSE if function should return
**                    right part
**
** @return     Left or Right half respectively
*/

t_ull	split_block(t_ull block, t_bool left)
{
	return ((left ? block >> 32 : block) & 0xFFFFFFFF);
}

/*
** @brief      Cut 8 bytes from the unsigned string into t_ull <block>.
**
** @param      str   The string
**
** @return     64-bit block
*/

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

/*
** @brief      Ask user to provide key and/or IV. Input is written into the
**             <key> and/or <iv> fields of <options> structure.
**
** @errors      [IVERROR]     If operating in cbc mode and key is provided, it
**                            is obligatory to proved Initializing Vector too.
**
** @param      args     The arguments
** @param      options  The options
*/

void	ask_key_vector(t_options *options)
{
	if (ft_endswith(options->command, "cbc") &&
		options->key_provided && !options->iv_provided)
	{
		ft_panic(1, "iv undefined");
	}
	if (!ft_strequ(options->command, "base64"))
	{
		if (!options->key_provided)
			read_key(options);
		if (!options->iv_provided && ft_endswith(options->command, "cbc"))
			read_iv(options);
	}
}

/*
** @brief      Read the key from stdin.
**
** @note       I need to reopen stdin stream to accept user input when plaintext
**             was provided through the pipeline (echo "hello" | ./ft_ssl des)
**
** @param      options  The options
*/

void	read_key(t_options *options)
{
	char	*key;

	ft_dprintf(2, "enter des key in hex: ");
	if (options->fd_from == 0)
		freopen("/dev/tty", "r", stdin);
	ft_gnl(0, &key);
	if (key == NULL)
	{
		ft_dprintf(2, "\nbad password read\n");
		exit(1);
	}
	else if (*key == '\0')
		exit(0);
	options->key = valid_hex(key, "key");
	free(key);
}

/*
** @brief      Read the Initializing Vector from standard input
**
** @note       Terminal file get's reopened, in case any writer sends EOF.
**             Anything that comes from the pipeline *must* be processed
**             beforehand.
**
** @param      options  The options
*/

void	read_iv(t_options *options)
{
	char	*iv;

	ft_dprintf(2, "enter initial vector: ");
	if (options->fd_from == 0)
		freopen("/dev/tty", "r", stdin);
	ft_gnl(0, &iv);
	if (iv == NULL)
	{
		ft_dprintf(2, "\nbad iv read\n");
		exit(1);
	}
	else if (*iv == '\0')
		exit(0);
	options->iv = parse_hex(valid_hex(pad_key(iv, 16), "iv"));
	free(iv);
}
