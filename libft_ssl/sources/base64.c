/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:17:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/11 11:32:47 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*base64_encode(char *input)
{
	char *ret = NULL;
	asprintf(&ret, "base64_encode was called! input is %s\n", input);
	return (ret);
}