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