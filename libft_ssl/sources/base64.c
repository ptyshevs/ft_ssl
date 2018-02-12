/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:17:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 09:18:20 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char index_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
	'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a',
	'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9', '+', '/'};

char	*base64_encrypt(char *input)
{
	char *ret = NULL;
	asprintf(&ret, "base64_encode was called! input is %s\n", input);
	return (ret);
}

/*
** @brief      Base64 is a binary-to-text encoding using ASCII format
** 
** @note       All your base are 64
**
** @param      options  The options
**
** @return     1 if success, anything else otherwise (like, really, anything)
*/

int		base64(t_options *options)
{
	char	*in;
	char	*out;

	in = read_fd(options->fd_from, 100);
	printf("base64, baby!\n");
	if (options->encrypt)
		out = base64_encrypt(in);
	else
		out = base64_decrypt(in);
	ft_dprintf(options->fd_to, "%s\n", out);
	return (1);
}
