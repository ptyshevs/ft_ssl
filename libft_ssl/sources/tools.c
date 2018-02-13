/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:03:42 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/13 22:46:56 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "tools.h"

char	*read_fd(int fd)
{
	char	*plaintext;
	char	*buf;

	plaintext = NULL;
	while (ft_gnl_enchanced(fd, &buf, TRUE) > 0)
		plaintext = ft_concat(plaintext, buf, TRUE);
	return (plaintext);
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
