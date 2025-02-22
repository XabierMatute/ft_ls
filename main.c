/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:45 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 14:02:20 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int is_flag_input(char const *str)
{
	if (str[0] == '-' && ft_strlen(str) > 1)
		return (1);
	return (0);
}

static t_flags get_flag(char const *str, t_flags flags)
{
	int i = 1;

	while (str[i])
	{
		switch (str[i])
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
				ft_eprintf("ls: invalid option '%c'\n", str[i]);
				ft_eprintf("Available options:\n");
				ft_eprintf("-l: Use a long listing format\n");
				ft_eprintf("-R: Recursive listing of subdirectories\n");
				ft_eprintf("-a: Include entries which start with .\n");
				ft_eprintf("-r: Reverse the order while sorting\n");
				ft_eprintf("-t: Sort by modification time, newest first\n");
				exit(2);
				break;
		}
		i++;
	}
	
	return (flags);
}

static t_flags get_flags(int argc, char const *argv[])
{
	t_flags flags;
	int				i = 1;

	ft_bzero(&flags, sizeof(t_flags));

	while (i < argc)
	{
		if (is_flag_input(argv[i]))
			flags = get_flag(argv[i], flags);
		i++;
	}
	return (flags);
}

static int	count_paths(int argc, char const *argv[])
{
	int	c = 0;

	while (--argc)
		if (!is_flag_input(argv[argc]))
			c++;
	return (c);
}

static char **get_paths(int argc, char const *argv[])
{
	char **paths = ft_calloc(count_paths(argc, argv) + 1, sizeof(char *));
	int 	i = 0;

	if (!paths)
	{
		ft_eprintf("Memory Error: could not allocate %i bits\n", count_paths(argc, argv) + 1, sizeof(char *));	
		perror("Malloc: ");
		exit(errno);
	}	
	while (--argc)
		if (!is_flag_input(argv[argc]))
			paths[i++] = ft_strdup(argv[argc]);
	return(paths);
}

static int parse_imput(int argc, char const *argv[])
{
	const t_flags	flags = get_flags(argc, argv);
	char			**paths = get_paths(argc, argv);

	ft_ls(paths, flags);
	free2((void **)paths);
	return (0);
}

int main(int argc, char const *argv[])
{
	return (parse_imput(argc, argv));
}
