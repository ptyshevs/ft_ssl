/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:37:26 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/13 18:36:59 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_parse.h"

t_bool				is_valid_hex(char *nbr)
{
	while (*nbr)
	{
		if (!((*nbr >= 48 && *nbr <= 57) || (*nbr >= 65 && *nbr <= 70) ||
			(*nbr >= 97 && *nbr <= 102)))
			return (FALSE);
		nbr++;
	}
	return (TRUE);
}

char				*valid_hex(char *nbr, char *type)
{
	if (ft_strequ(type, "key") && !is_valid_hex(nbr))
	{
		ft_dprintf(2, "non-hex digit\ninvalid hex key value\n");
		exit(1);
	}
	else if (ft_strequ(type, "iv") && !is_valid_hex(nbr))
	{
		ft_dprintf(2, "non-hex digit\ninvalid hex iv value\n");
		exit(1);
	}
	else
		return (nbr);
}

unsigned long long	parse_hex(char *nbr)
{
	unsigned long long	res;
	char				*tmp;
	size_t				i;

	tmp = nbr;
	res = 0;
	i = 0;
	while (i < 16)
	{
		res *= 16;
		if (nbr[i] >= 48 && nbr[i] <= 57)
			res += nbr[i] - '0';
		else if (nbr[i] >= 65 && nbr[i] <= 70)
			res += 10 + nbr[i] - 'A';
		else if (nbr[i] >= 97 && nbr[i] <= 102)
			res += 10 + nbr[i] - 'a';
		i++;
	}
	free(tmp);
	return (res);
}


/*
** @brief      if key is shorter than 64 bit, pad it with zeros. If it's longer,
**             trim it.
**
** @param      key   The key
*/

char	*pad_key(char *key, size_t len)
{
	char *tmp;

	key = ft_sprintf("%.*s", len, key);
	if (ft_slen(key) < len)
	{
		tmp = ft_strnew(48);
		ft_memset(tmp, '0', len - ft_slen(key));
		key = ft_concat(key, tmp, TRUE);
	}
	return (key);
}
