/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:12:18 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/11 18:16:19 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_parse.h"
#include "ft_ssl.h"

int		main(int ac, char **av)
{
	t_args *args = arg_parse(ac, av);
	if (is_valid_command(args))
		dispatch(args);
	else
		return (display_usage(args));
	return (0);
}