//
// Created by xmatute- on 7/3/24.
//

#include "get_flags.h"

t_flags get_flags(int argc, char const *argv[])
{
	t_flags flags;

	flags = (t_flags){};
	while (argc--)
	{
		if (argv[argc][0] == '-')
		{
			while (*++argv[argc])
			{
				if (*argv[argc] == 'l')
					flags.l = 1;
				else if (*argv[argc] == 'R')
					flags.R = 1;
				else if (*argv[argc] == 'a')
					flags.a = 1;
				else if (*argv[argc] == 'r')
					flags.r = 1;
				else if (*argv[argc] == 't')
					flags.t = 1;
				else
				{
					ft_putstr_fd("ft_ls: illegal option -- ", 2);
					ft_putchar_fd(*argv[argc], 2);
					ft_putchar_fd('\n', 2);
					ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
					exit(1);
				}
			}
		}
	}
	return (flags);
}