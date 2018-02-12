/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:17:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 18:12:31 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** index table
*/

char g_it[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
	'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a',
	'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9', '+', '/'};

char	*append_pad(char *ret, char *in, int pad, int i)
{
	int	octet;
	int	len;

	if (pad)
	{
		octet = 0;
		len = 4 - pad;
		while (pad && len--)
			octet = (octet << 8) + *in++;
		octet = octet << (8 * (pad - 1));
		ret[i] = 4 - pad > 0 ? g_it[(octet & 16515072) >> 18] : '=';
		ret[i + 1] = 3 - pad > 0 ? g_it[(octet & 258048) >> 12] : '=';
		ret[i + 2] = 2 - pad > 0 ? g_it[(octet & 4032) >> 6] : '=';
		ret[i + 3] = 1 - pad > 0 ? g_it[octet & 63] : '=';
	}
	return (ret);
}

t_bool	is_valid_base64(char *s)
{
	int	i;

	while (*s)
	{
		i = 0;
		while (i < 64)
		{
			if (g_it[i] == *s)
				break ;
			i++;
		}
		if (i == 64)
			return (FALSE);
		s++;
	}
	return (TRUE);
}

char	*base64_encrypt(char *in)
{
	char	*ret;
	int		i;
	long	octet;
	int		out_len;
	int		pad;

	out_len = ft_slen(in) + ft_slen(in) / 3;
	out_len += ft_slen(in) % 3 == 0 ? 0 : 1;
	pad = (4 - (out_len % 4)) % 4;
	out_len += (4 - (out_len % 4)) % 4;
	ret = ft_strnew(out_len);
	i = 0;
	while (ft_slen(in) / 3)
	{
		octet = (*in << 16) + (*(in + 1) << 8) + (*(in + 2));
		in += 3;
		ret[i] = g_it[(octet & 16515072) >> 18];
		ret[i + 1] = g_it[(octet & 258048) >> 12];
		ret[i + 2] = g_it[(octet & 4032) >> 6];
		ret[i + 3] = g_it[octet & 63];
		i += 4;
	}
	return (append_pad(ret, in, pad, i));
}

char	*base64_decrypt(char *in)
{
	(void)in;
	return (NULL);
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
	out = options->encrypt ? base64_encrypt(in) : base64_decrypt(in);
	if (out)
		ft_dprintf(options->fd_to, options->fd_to == 1 ? "%s\n" : "%s", out);
	return (1);
}
