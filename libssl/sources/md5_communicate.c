#include <structures.h>
#include "ft_printf.h"

void	md5_usage(void)
{
	ft_printf("usage: md5 [-pqr] [-s string] [files ...]\n");
}

void	md5_invalid_opt(char *option)
{
	ft_printf("md5: option requires an argument -- s\n");
	md5_usage();
	exit(1);
}

void	show_len(t_uc *len)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		ft_printf("[%d]: %08b\n", i, len[i]);
		i++;
	}
}

void	show_block(t_inp *inp)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		ft_printf("%08b ", inp->block[i]);
		if (i > 1 && i % 8 == 7)
			ft_printf("\n");
		i++;
	}
}

