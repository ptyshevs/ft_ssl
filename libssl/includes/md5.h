/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:12:28 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/11/22 23:12:36 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include "libft.h"
# include "structures.h"

typedef struct	s_md5
{
	t_uint	A;
	t_uint	B;
	t_uint	C;
	t_uint	D;

	t_uint	A_prev;
	t_uint	B_prev;
	t_uint	C_prev;
	t_uint	D_prev;
	t_uint			X[16];
	t_uint			M[64];
}				t_md5;


t_uint	F(t_uint x, t_uint y, t_uint z);
t_uint	G(t_uint x, t_uint y, t_uint z);
t_uint	H(t_uint x, t_uint y, t_uint z);
t_uint	I(t_uint x, t_uint y, t_uint z);

t_uint	left_rotate(t_uint val, t_uint shift, t_uint type_len);
t_md5	*init_state(void);
void	md5_padding(t_inp *inp);
void	md5_block(t_inp *inp, t_md5 *st);
void	md5_show_digest(t_options *opt, t_md5 *st);


static t_uc g_md5_trans[64] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
		5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
		0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};

static t_uc g_md5_shifts[64] = {
		7, 12, 17, 22,
		7, 12, 17, 22,
		7, 12, 17, 22,
		7, 12, 17, 22,
		5, 9, 14, 20,
		5, 9, 14, 20,
		5, 9, 14, 20,
		5, 9, 14, 20,
		4, 11, 16, 23,
		4, 11, 16, 23,
		4, 11, 16, 23,
		4, 11, 16, 23,
		6, 10, 15, 21,
		6, 10, 15, 21,
		6, 10, 15, 21,
		6, 10, 15, 21
};

#endif
