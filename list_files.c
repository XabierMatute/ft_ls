/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:24:39 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 20:56:52 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void list_file(const char *path, const t_flags flags, char *dir_path)
{
    put_file(path, flags, dir_path);
}

int list_files_r(char **paths, const t_flags flags, char *dir_path)
{
    size_t i = 0;

    while (paths[i])
        i++;
    while (i--)
        list_file(paths[i], flags, dir_path);
    return (0);
}

int list_files(char **paths, const t_flags flags, char *dir_path)
{
    if (flags.r)
    {
        return (list_files_r(paths, flags, dir_path));
    }
	while (*paths)
	{
		list_file(*paths, flags, dir_path);
		paths++;
	}
	return (0);
}

int list_only_files_r(char **paths, const t_flags flags, char *dir_path)
{
    size_t i = 0;

    while (paths[i])
        i++;
    while (i--)
        if (!isdir(paths[i], dir_path))
            list_file(paths[i], flags, dir_path);
    return (0);
}

int list_only_files(char **paths, const t_flags flags, char *dir_path)
{
    if (flags.r)
    {
        return (list_only_files_r(paths, flags, dir_path));
    }
	while (*paths)
	{
		if (!isdir(*paths, dir_path))
			list_file(*paths, flags, dir_path);
		paths++;
	}
	return (0);
}