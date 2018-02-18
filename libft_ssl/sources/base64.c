/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:17:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 15:29:41 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "tools.h"

/*
** @brief      Encrypt plaintext into base64
**
** @param      in    plaintext
**
** @return     base64 cipher text
*/

void	base64_encrypt(t_line *in, t_line *out)
{
	long long	len;
	int			i;
	t_ull		octet;
	size_t		j;

	len = (long long)in->len;
	out->len = (size_t)(len + len / 3 + (len % 3 == 0 ? 0 : 1));
	out->len += (4 - (out->len % 4)) % 4;
	out->str = ft_memalloc(out->len);
	i = 0;
	j = 0;
	while (len > 0)
	{
		octet = (in->str[j] << 16) | (j + 1 < in->len ?  (in->str[j + 1] << 8) : (t_ull)0);
		octet |= j + 2 < in->len ? in->str[j + 2] : 0;
		j += 3;
		len -= 3;
		out->str[i++] = g_it[(octet >> 18) & 0x3F];
		out->str[i++] = g_it[(octet >> 12) & 0x3F];
		out->str[i++] = len < -1 ? (char)'=' : g_it[(octet >> 6) & 0x3F];
		out->str[i++] = len < 0 ? (char)'=' : g_it[octet & 0x3F];
	}
}

/*
** @brief      Decrypt Base64, while ignoring newlines
**
** @param      in    Base64 string
**
** @return     Plaintext
*/

void	base64_decrypt(t_line *in, t_line *out)
{
	long long	len;
	int			j;
	int			octet;
	size_t		k;

	len = (long long)in->len;
	out->str = (t_uc *)ft_strnew(in->len - in->len / 4);
	k = 0;
	while ((len -= 4) >= 0)
	{
		j = 3;
		octet = 0;
		while (j >= 0)
		{
			while (k < in->len && !ft_strchr((char *)g_it, in->str[k]))
				k++;
			octet += ft_strchr((char *)g_it, in->str[k])[0] << (6 * j--);
		}
		j = 2;
		while (j >= 0)
			out->str[out->len++] = (t_uc)((octet >> (8 * j--)) & 255);
	}
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

int		base64(t_options *options, t_line *in)
{
	t_line	*out;

	out = init_line();
	options->encrypt ? base64_encrypt(in, out) : base64_decrypt(in, out);
	out ? out_base64(options->fd_to, out, options->encrypt) : NULL;
	clean_t_line(&out);
	return (1);
}
