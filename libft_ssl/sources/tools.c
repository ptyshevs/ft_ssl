/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:03:42 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 09:16:05 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_fd(int fd, int bufsize)
{
	char	*plaintext;
	char	*tmp;
	char	buf[bufsize + 1];
	int		r;

	plaintext = NULL;
	while ((r = read(fd, buf, bufsize)) > 0)
	{
		buf[r] = '\0';
		tmp = plaintext;
		plaintext = ft_concat(plaintext, buf, FALSE);
		free(tmp);
	}
	return (plaintext);
}