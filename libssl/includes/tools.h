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

# include "libft.h"
# include "ft_gnls.h"
# include "structures.h"

/*
** index table for Base64 encoding
*/

static char	*g_b64 = \
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

t_line				*ft_read_fd_to_line(int fd, t_bool ignore_newlines);
void				ask_key_vector(t_options *options);
void				read_key(t_options *options);
void				read_iv(t_options *options);

t_ull				split_block(t_ull block, t_bool left);
void				block_to_str(t_ull block, t_line *out, int j,
								t_bool last_block);
t_ull				apply_key(t_ull block, t_ull subkey);
t_ull				str_to_block(t_uc *str);
t_ull				add_padding(t_uc *remainder, long long value);

t_ull				ft_rot(t_ull num, t_ull mask, int shift, t_bool left);
t_ull				*get_subkeys(t_ull *keys, t_ull key, t_bool encrypt);
t_ull				expand_block(t_ull block);

void				display_key_iv(t_options *options);
void				out_base64(int fd, t_line *b64, t_bool x64);
void				out_des(t_options *options, t_line *out);

char				*valid_hex(char *nbr, char *type);
t_ull				parse_hex(char *nbr);
char				*pad_key(char *key, size_t len);

void				md5_invalid_opt(char *option);
t_command			*map_command(char *command);
t_options			*parse_opt(t_cmd_type type, char **options);
void				show_inp_sources(t_list *inp_srcs);
t_inp				*init_input(t_command *command, t_options *opt, t_inp_src *src);
void				next_block(t_inp *inp);
void				show_block(t_inp *inp);

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

void	md5_padding(t_inp *inp);
void	md5_block(t_inp *inp, t_md5 *st);

#endif
