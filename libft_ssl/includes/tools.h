/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:10:29 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/18 15:08:38 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

/*
** index table
*/

static t_uc	*g_it = \
	(t_uc *)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char	*g_b64 = \
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

t_line				*ft_read_fd_to_line(int fd, t_bool ignore_newlines);
void				ask_key_vector(t_args *args, t_options *options);
void				read_key(t_options *options);
void				read_iv(t_options *options);

t_ull				split_block(t_ull block, t_bool left);
void				block_to_str(t_ull block, t_line *out, int j,
								t_bool last_block);
t_ull				apply_key(t_ull block, t_ull subkey);
t_ull				str_to_block(t_uc *str);
t_ull				add_padding(t_uc *remainder, long long value);

t_ull				ft_rot(t_ull num, t_ull mask, int shift, t_bool left);
t_ull * get_subkeys(t_ull *keys, t_ull key, t_bool encrypt);
t_ull				expand_block(t_ull block);

int					get_index(char c);
void				out_base64(int fd, t_line *b64, t_bool x64);
void				out_des(t_options *options, t_line *out);

char				*valid_hex(char *nbr, char *type);
unsigned long long	parse_hex(char *nbr);
char				*pad_key(char *key, size_t len);

#endif
