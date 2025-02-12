/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:10:23 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 20:57:34 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
// #include <stdio.h>

// void print_paths(char **paths)
// {
// 	int i = 0;

// 	while (paths[i])
// 	{
// 		printf("path[%i]: %s\n", i, paths[i]);
// 		i++;
// 	}
// }

int list_paths(char **paths, const t_flags flags, char *dir_path)
{
	paths = sort_paths(paths, flags, dir_path);
	list_only_files(paths, flags, dir_path);
	ft_putchar('\n');
	list_directories(paths, flags, dir_path);
	return (0);
}
