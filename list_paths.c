/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:10:23 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 18:22:36 by xmatute-         ###   ########.fr       */
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

int list_paths(char **paths, const t_flags flags)
{
	paths = sort_paths(paths, flags);
	list_only_files(paths, flags);
	list_directories(paths, flags);
	return (0);
}
