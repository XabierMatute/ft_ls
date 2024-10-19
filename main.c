/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:45 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/14 15:42:15 by xmatute-         ###   ########.fr       */
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
			int j = 1;

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
					ft_eprintf("ls: invalid option -- '%c'\n", argv[i][j]);
					ft_eprintf("Available options:\n");
					ft_eprintf("-l: Use a long listing format\n");
					ft_eprintf("-R: Recursive listing of subdirectories\n");
					ft_eprintf("-a: Include entries which start with .\n");
					ft_eprintf("-r: Reverse the order while sorting\n");
					ft_eprintf("-t: Sort by modification time, newest first\n");
					exit(2);
					break;
				}
				j++;
			}
		}
		i++;
	}
	return (flags);
}

int	count_paths(int argc, char const *argv[])
{
	int	c = 0;

	while (--argc)
		if (argv[argc][0] != '-')
			c++;
	return (c);
}

char **get_paths(int argc, char const *argv[])
{
	char **paths = ft_calloc(count_paths(argc, argv) + 1, sizeof(char *));
	int 	i = 0;

	while (--argc)
		if (argv[argc][0] != '-')
			paths[i++] = ft_strdup(argv[argc]);
	return(paths);
}

static int parse_imput(int argc, char const *argv[])
{
	const t_flags	flags = get_flags(argc, argv);
	
	char		**paths = get_paths(argc, argv);
	
	ft_ls(paths, flags);
	free2((void **)paths);
	return (0);
}

int main(int argc, char const *argv[])
{
	return (parse_imput(argc, argv));
}
