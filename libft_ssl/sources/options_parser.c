/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:51:37 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/02/23 16:19:11 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "arg_tools.h"

/*
** @brief      Initialize options data structure
**
** @param      command  The command string (validated, hopefully)
**
** @return     Initialized options
*/

t_options	*init_options(char *command)
{
	t_options *opt;

	opt = (t_options *)malloc(sizeof(t_options));
	opt->fd_from = 0;
	opt->fd_to = 1;
	opt->base64 = FALSE;
	opt->encrypt = TRUE;
	opt->key = 0;
	opt->key_provided = FALSE;
	opt->iv = 0;
	opt->iv_provided = FALSE;
	opt->print_key_iv = FALSE;
	opt->command = command;
	return (opt);
}

/*
** @brief      Determines if option is valid, according to the global array of
**             supported options.
**
** @param      option  The option data structure
**
** @return     TRUE if option is valid, FALSE otherwise.
*/

t_bool		is_valid_option(char *option)
{
	int		i;

	i = 0;
	while (g_options_provided[i])
	{
		if (ft_strequ(option, g_options_provided[i++]))
			return (TRUE);
	}
	return (FALSE);
}

/*
** @brief      Parse main flags: encrypt/decrypt and input/output.
**             Check for invalid options is also performed.
**
** @errors     [ERROPT]  if options has not been found in the list of supported,
**             usage is displayed, and program exits.
**
** @param      args  The arguments
** @param      opt   The options structure
**
** @return     pointer to options structure
*/

t_options	*parse_core_flags(t_args *args, t_options *opt)
{
	int		i;

	i = 0;
	while (args->options && args->options[i])
	{
		if (ft_strequ(args->options[i], "-e"))
			opt->encrypt = TRUE;
		else if (ft_strequ(args->options[i], "-d"))
			opt->encrypt = FALSE;
		else if (ft_strequ(args->options[i], "-i"))
			handle_file(&opt->fd_from, args->options[i++ + 1], TRUE);
		else if (ft_strequ(args->options[i], "-o"))
			handle_file(&opt->fd_to, args->options[i++ + 1], FALSE);
		else if (ft_strequ(args->options[i], "-k") && (opt->key_provided = TRUE))
			args->options[i + 1] == NULL ? display_options_and_exit(NULL) :
			(opt->key = valid_hex(args->options[i++ + 1], "key"));
		else if (ft_strequ(args->options[i], "-v") && (opt->iv_provided = TRUE))
			args->options[i + 1] == NULL ? display_options_and_exit(NULL) :
			(opt->iv = parse_hex(valid_hex(pad_key(args->options[i++ + 1], 16),
										"iv")));
		else if (!ft_strequ(args->options[i], "-a") && !ft_strequ(args->options[i], "-p"))
			display_options_and_exit(args->options[i]);
		i++;
	}
	return (opt);
}

/*
** @brief      Parse options routine.
**
**             Parsing of core flags is called first, as well as options
**             validation.
**
**             Additional flags are processed here: -k, -v, -a and -p.
**
** @notes      Subtleties:
**               - if -k or -v flag found, and the next argument is not a valid
**                 number in hex format, error is displayed and program exits.
**               - key is stored as a string and it's processing is delayed
**                 until the dispatch() routine. On the contrary, IV is
**                 validated and transformed into a number in-place.
**
** @param      args  The arguments
**
** @return     options structure
*/

t_options	*parse_options(t_args *args)
{
	t_options	*opt;
	int			i;

	opt = parse_core_flags(args, init_options(args->command));
	i = 0;
	while (args->options && args->options[i])
	{
		if (ft_strequ(args->options[i], "-a"))
			opt->base64 = TRUE;

		else if (ft_strequ(args->options[i], "-p"))
			opt->print_key_iv = TRUE;
		i++;
	}
	return (opt);
}
