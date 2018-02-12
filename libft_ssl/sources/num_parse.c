/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:37:26 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/12 07:31:27 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_parse.h"

t_bool				is_valid_hex(char *nbr)
{
	while (*nbr)
	{
		if (!((*nbr >= 48 && *nbr <= 57)) || (*nbr >= 65 && *nbr <= 70) ||
			(*nbr >= 97 && *nbr <= 102))
			return (FALSE);
		nbr++;
	}
	return (TRUE);
}

char				*validate_hex(char *nbr, char *type)
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

	res = 0;
	while (*nbr)
	{
		res *= 16;
		if (*nbr >= 48 && *nbr <= 57)
			res += *nbr - '0';
		else if (*nbr >= 65 && *nbr <= 70)
			res += 10 + *nbr - 'A';
		else if (*nbr >= 97 && *nbr <= 102)
			res += 10 + *nbr - 'a';
		nbr++;
	}
	return (res);
}
