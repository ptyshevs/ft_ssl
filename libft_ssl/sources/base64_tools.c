/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 20:36:18 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 21:26:25 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "tools.h"

t_bool	is_valid_base64(char *s)
{
	int	i;

	while (*s)
	{
		i = 0;
		while (i < 64)
		{
			if (g_it[i] == *s)
				break ;
			i++;
		}
		if (i == 64)
			return (FALSE);
		s++;
	}
	return (TRUE);
}

/*
** @brief      Format base64 encrypt/decrypt string as it is in OpenSSL:
**             newline every 64 characters + at the end of string
** @param      fd    file descriptior to write to
** @param      b64   Base64 string
*/

void	output_base64(int fd, char *b64, t_bool x64)
{
	int	cnt_lbreaks;

	if (x64)
	{
		cnt_lbreaks = ft_slen(b64) / 64;
		while (cnt_lbreaks--)
		{
			ft_dprintf(fd, "%.64s\n", b64);
			b64 += 64;
		}
		ft_dprintf(fd, "%s\n", b64);
	}
	else
		ft_dprintf(fd, "%s", b64);
}
