/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:03:42 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 12:53:24 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "tools.h"

t_line	*ft_read_fd_to_line(int fd)
{
	t_uc	buf[8000];
	t_line	*content;
	t_ull	size;
	int		r;

	content = init_line();
	size = 1;
	while ((r = read(fd, buf, 8000)) > 0)
	{
		while (content->len + r >= size)
		{
			content->str = ft_realloc(content->str, content->len,
									size * 2, TRUE);
			size *= 2;
		}
		ft_memcpy(content->str + content->len, buf, r);
		content->len += r;
	}
	return (content);
}

/*
** @brief      Format base64 encrypt/decrypt string as it is in OpenSSL:
**             newline every 64 characters + at the end of string
** @param      fd    file descriptior to write to
** @param      b64   Base64 string
*/

void	out_base64(int fd, t_line *b64, t_bool x64)
{
	long long	cnt_lbreaks;
	int			shift;

	shift = 0;
	if (x64)
	{
		cnt_lbreaks = (long long) (b64->len / 64);
		while (cnt_lbreaks--)
		{
			write(fd, b64->str + shift, 64);
			write(fd, "\n", 1);
			// ft_dprintf(fd, "%.64s\n", b64);
			shift += 64;
		}
		write(fd, b64->str + shift, &b64->str[b64->len] - (b64->str + shift));
		write(fd, "\n", 1);
		// ft_dprintf(fd, "%s\n", b64);
	}
	else
	{
		write(fd, b64->str, b64->len);
		// ft_dprintf(fd, "%s", b64);
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

	ft_printf("enter des key in hex: ");
	freopen("/dev/tty", "r", stdin);
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
