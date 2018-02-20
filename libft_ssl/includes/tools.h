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
void				read_key(t_options *options);

int					get_index(char c);
void				out_base64(int fd, t_line *b64, t_bool x64);
void				output_des(int fd, char *des, int len, t_bool x64);

char				*valid_hex(char *nbr, char *type);
unsigned long long	parse_hex(char *nbr);
char				*pad_key(char *key);

#endif
