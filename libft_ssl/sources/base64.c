/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:17:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 11:13:14 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char it[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
	'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a',
	'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9', '+', '/'};

char	*base64_encrypt(char *in)
{
	char	*ret;
	int		i;
	long	octet;

	int out_len = ft_slen(in) + ft_slen(in) / 3;
	int pad = (4 - (out_len % 4)) % 4;
	out_len += (4 - (out_len % 4)) % 4;
	ft_printf("pad = %d | allocated len = %d\n", pad, out_len);
	ret = ft_strnew(out_len);
	int len = ft_slen(in) / 3;
	i = 0;
	while (len--)
	{
		octet = (*in << 16) + (*(in + 1) << 8) + (*(in + 2));
		in += 3;
		ret[i] = it[(octet & 16515072) >> 18];
		ret[i + 1] = it[(octet & 258048) >> 12];
		ret[i + 2] = it[(octet & 4032) >> 6];
		ret[i + 3] = it[octet & 63];
		i+= 4;
	}
	if (pad)
	{
		octet = 0;
		len = 4 - pad;
		while (pad && len--)
		{
			ft_printf("extracting char (%c|%d)\n", *in, *in);
			octet = (octet << 8) + *in++;
		}
		octet = octet << (8 * (pad - 1));
		ret[i] = (octet & 16515072) >> 18 == 0 ? '=' : it[(octet & 16515072) >> 18];
		ret[i + 1] = (octet & 258048) >> 12 == 0 ? '=' : it[(octet & 258048) >> 12];
		ret[i + 2] = (octet & 4032) >> 6 == 0 ? '=' : it[(octet & 4032) >> 6];
		ret[i + 3] = octet & 63 ? it[octet & 63] : '=';
		ft_printf("last block octet: %d\n", octet);
	}
	return (ret);
}

char	*base64_decrypt(char *in)
{
	(void)in;
	return(NULL);
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
	ft_printf("base64, baby!\n");
	if (options->encrypt)
		out = base64_encrypt(in);
	else
		out = base64_decrypt(in);
	ft_dprintf(options->fd_to, "%s\n", out);
	return (1);
}
