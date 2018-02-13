/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:58:45 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/13 18:47:27 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "tools.h"

void	read_key(t_options *options)
{
	char	*key;

	ft_printf("enter des key in hex: ");
	ft_gnl(0, &key);
	if (key == NULL)
	{
		ft_dprintf(2, "\nbad password read\n");
		exit(1);
	}
	else if (*key == '\0')
		exit(0);
	options->key = parse_hex(valid_hex(pad_key(key), "key"));
	free(key);
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
	if (!options->key_provided)
		read_key(options);
	ft_printf("key: %llu\n", options->key);
	system("leaks ft_ssl");
	return (1);
}
