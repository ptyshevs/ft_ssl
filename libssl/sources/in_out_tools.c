/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:03:42 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 12:15:31 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** @brief      Read content of the File Descriptor into t_line data structure.
**
** @param      fd               File Descriptor
** @param      ignore_newlines  (t_bool) True if I should ignore newlines, False
**                              otherwise
**
** @return     Read content in form of unsigned char string + len data structure
*/

t_line	*ft_read_fd_to_line(int fd, t_bool ignore_newlines)
{
	t_uc	buf[8000];
	t_line	*content;
	t_ull	size;
	ssize_t	r;
	int		i;

	content = init_line();
	size = 1;
	while ((r = read(fd, buf, 8000)) > 0)
	{
		i = 0;
		while (content->len + r >= size)
		{
			content->str = ft_realloc(content->str, content->len,
									size * 2, True);
			size *= 2;
		}
		while (ignore_newlines && i < r)
			if (buf[i++] != '\n')
				content->str[content->len++] = buf[i - 1];
		!ignore_newlines ? ft_memcpy(content->str + content->len, buf, r) : 0;
		content->len += ignore_newlines ? 0 : r;
	}
	return (content);
}

/*
** @brief      Format base64 encrypt/decrypt string as it is in OpenSSL: newline
**             every 64 characters + at the end of string
**
** @param      fd    file descriptior to write to
** @param      b64   t_line, containing Base64-encoded string
** @param      x64   If True, function adds linebreak every 64 symbols.
**                   If False, output is written in one continuous string
*/

void	out_base64(int fd, t_line *b64, t_bool x64)
{
	long long	cnt_lbreaks;
	size_t		shift;

	shift = 0;
	if (x64)
	{
		cnt_lbreaks = (long long)(b64->len / 64);
		while (cnt_lbreaks--)
		{
			write(fd, b64->str + shift, 64);
			write(fd, "\n", 1);
			shift += 64;
		}
		write(fd, b64->str + shift, &b64->str[b64->len] - (b64->str + shift));
		if (shift < b64->len)
			write(fd, "\n", 1);
	}
	else
		write(fd, b64->str, b64->len);
}

/*
** @brief      Output DES in appropriate format
**
** @param      options  The options
** @param      out      The output t_line DS
*/

void	out_des(t_options *options, t_line *out)
{
	t_line	*tmp;

	tmp = init_line();
	if (out->str)
	{
		if (options->base64 && options->encrypt)
		{
			base64_encrypt(out, tmp);
			ft_tline_replace(out, tmp);
		}
		options->base64 ? out_base64(options->fd_to, out, options->encrypt) :
		write(options->fd_to, out->str, out->len);
	}
	clean_t_line(&tmp);
}
