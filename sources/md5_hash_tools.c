/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:13:11 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/22 23:13:12 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

t_uint	F(t_uint x, t_uint y, t_uint z)
{
	return ((x & y) | ((~x) & z));
}

t_uint	G(t_uint x, t_uint y, t_uint z)
{
	return ((x & z) | (y & (~z)));
}

t_uint H(t_uint x, t_uint y, t_uint z)
{
	return (x ^ y ^ z);
}

t_uint I(t_uint x, t_uint y, t_uint z)
{
	return (y ^ (x | (~z)));
}
