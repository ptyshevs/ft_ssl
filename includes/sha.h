/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:00:57 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/24 14:01:32 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_H
# define SHA_H
#include <md5.h>
#include "structures.h"

void	sha256_block(t_inp *inp, t_md5 *st);


#endif
