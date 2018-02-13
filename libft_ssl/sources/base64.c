/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:17:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/13 23:12:21 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "tools.h"

/*
** @brief      Add padding at the end of base64 string, if the last octet is not
**             full.
**
** @param      ret   base64 string
** @param      in    plaintext
** @param      pad   padding - the number of '=' to be added
** @param      i     current position in base64 string
**
** @return     base64 string with appended padding.
*/

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

/*
** @brief      Encrypt plaintext into base64
**
** @param      in    plaintext
**
** @return     base64 cipher text
*/

char	*base64_encrypt(char *in, int len)
{
	char	*ret;
	int		i;
	long	octet;
	int		out_len;
	int		pad;

	out_len = len + len / 3 + (len % 3 == 0 ? 0 : 1);
	pad = (4 - ((out_len) % 4)) % 4;
	out_len += (4 - (out_len % 4)) % 4;
	ret = ft_strnew(out_len);
	i = 0;
	while ((len -= 3) >= 0)
	{
		octet = (*in << 16) + (*(in + 1) << 8) + *(in + 2);
		in += 3;
		ret[i++] = g_it[(octet & 16515072) >> 18];
		ret[i++] = g_it[(octet & 258048) >> 12];
		ret[i++] = g_it[(octet & 4032) >> 6];
		ret[i++] = g_it[octet & 63];
	}
	return (append_pad(ret, in, pad, i));
}

/*
** @brief      Map ASCII char to it's index in base64 index table.
**
** @param      c     char
**
** @return     The index.
*/

int		get_index(char c)
{
	int i;

	i = 0;
	while (i < 64)
	{
		if (g_it[i] == c)
			return (i);
		i++;
	}
	return (0);
}

/*
** @brief      Decrypt Base64, while ignoring newlines
**
** @param      in    Base64 string
**
** @return     Plaintext
*/

char	*base64_decrypt(char *in, int len)
{
	char	*ret;
	int		octet;
	int		i;

	ret = ft_strnew(len - len / 4);
	i = 0;
	while ((len -= 4) >= 0)
	{
		while (*in == '\n')
			in++;
		octet = (get_index(*in++) << 18);
		while (*in == '\n')
			in++;
		octet += (get_index(*in++) << 12);
		while (*in == '\n')
			in++;
		octet += get_index(*in++) << 6;
		while (*in == '\n')
			in++;
		octet += get_index(*in++);
		ret[i++] = (octet & 16711680) >> 16;
		ret[i++] = (octet & 65280) >> 8;
		ret[i++] = octet & 255;
	}
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

	in = read_fd(options->fd_from);
	out = options->encrypt ? base64_encrypt(in, ft_slen(in)) :
							base64_decrypt(in, ft_slen(in));
	if (out)
		output_base64(options->fd_to, out, options->encrypt);
	free(out);
	return (1);
}
