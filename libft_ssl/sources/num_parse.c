/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:37:26 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 15:53:19 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_tools.h"

/*
** @brief      Determines if string contains valid number in hex format.
**
** @param      nbr   The number string
**
** @return     TRUE if format is valid, FALSE otherwise.
*/

t_bool	is_valid_hex(char *nbr)
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

/*
** @brief      Pipe-like function to filter valid string containing hex number.
**             If format provided is invalid, program exits with an appropriate
**             message.
**
** @param      nbr   The number string
** @param      type  The type of parameter ("key" or "iv", accordingly)
**
** @return     <nbr> string if format is valid, exit with status 1 in case of
**             error encountered.
*/

char	*valid_hex(char *nbr, char *type)
{
	if (!is_valid_hex(nbr))
	{
		ft_dprintf(2, "non-hex digit\ninvalid hex %s value\n",
					ft_strequ(type, "key") ? "key" : "iv");
		exit(1);
	}
	else
		return (nbr);
}

/*
** @brief      Parse string containing hex number to t_ull variable.
**
** @param      nbr   The number string
**
** @return     unsigned long long int representation of the number provided.
*/

t_ull	parse_hex(char *nbr)
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
** @brief      if key is shorter than 64 bit, pad it with zeros on the left. If
**             it's longer, trim it to the appropriate size.
**
** @param      key   The key string
** @param      len   The desired length of the key
**
** @return     Padded key
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
