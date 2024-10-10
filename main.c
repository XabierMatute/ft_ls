/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:45 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/10 11:37:11 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_flags get_flags(int argc, char const *argv[])
{
	t_flags flags;
	int				i = 1;

	ft_bzero(&flags, sizeof(t_flags));

	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			int j = 0;

			while (argv[i][j])
			{
				switch (argv[i][j])
				{
				case 'l' :
					flags.l = 1;
					break;
				case 'R' :
					flags.R = 1;
					break;
				case 'a' :
					flags.a = 1;
					break;
				case 'r' :
					flags.r = 1;
					break;
				case 't' :
					flags.t = 1;
					break;
				default:
					break;
				}
				j++;
			}
		}
		i++;
	}
	return (flags);
}

static int parse_imput(int argc, char const *argv[])
{
	const t_flags	flags = get_flags(argc, argv);
	int				i = 1;
	int				ee = -42;

	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			ee = ft_ls(argv[i], flags);
			if (ee != 0)
				return (ee);
		}
		i++;
	}
	if (ee == -42)
		return (ft_ls(".", flags));
	return (0);
}

int main(int argc, char const *argv[])
{
	return (parse_imput(argc, argv));
}
