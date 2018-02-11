/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:17:31 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/11 16:14:01 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*base64_encode(char *input)
{
	char *ret = NULL;
	asprintf(&ret, "base64_encode was called! input is %s\n", input);
	return (ret);
}

/*
** @brief      Parse options, call base64
**
** @param      options  The options
**
** @return     { description_of_the_return_value }
*/

int		base64(char **options)
{
	(void)options;
	return (1);
}
