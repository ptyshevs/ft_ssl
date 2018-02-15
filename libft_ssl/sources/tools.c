/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:03:42 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/15 21:38:10 by ptyshevs         ###   ########.fr       */
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

t_node	*read_fd_to_list(int fd)
{
	t_node	*lst;
	char	*buf;

	lst = NULL;
	while (ft_gnl_enchanced(fd, &buf, TRUE) > 0)
	{
		expand_n(&lst, buf, ft_slen(buf));
		plaintext = ft_concat(plaintext, buf, TRUE);
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
