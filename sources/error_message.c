/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:48:15 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/23 19:48:25 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "ft_printf.h"

void	md5_usage(void)
{
	ft_printf("usage: md5 [-pqr] [-s string] [files ...]\n");
}

void	md5_invalid_opt(char *option)
{
	ft_printf("md5: option requires an argument -- %s\n", option);
	md5_usage();
	exit(1);
}

void	bad_read_error(char *filename)
{
	ft_printf("ft_ssl: %s: %s\n", filename, strerror(errno));
}
