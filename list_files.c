/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:24:39 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/21 19:59:07 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void list_file(const char *path, const t_flags flags)
{
    // ft_printf("listing: %s\n", path);
    put_file(path, flags);
}

int list_files_r(char **paths, const t_flags flags)
{
    size_t i = 0;

    while (paths[i])
        i++;
    while (i--)
        list_file(paths[i], flags);
    return (0);
}

int list_files(char **paths, const t_flags flags)
{
    if (flags.r)
    {
        return (list_files_r(paths, flags));
    }
	while (*paths)
	{
		list_file(*paths, flags);
		paths++;
	}
	return (0);
}

int list_only_files_r(char **paths, const t_flags flags)
{
    size_t i = 0;

    while (paths[i])
        i++;
    while (i--)
        if (!isdir(paths[i]))
            list_file(paths[i], flags);
    return (0);
}

int list_only_files(char **paths, const t_flags flags)
{
    if (flags.r)
    {
        return (list_only_files_r(paths, flags));
    }
	while (*paths)
	{
		if (!isdir(*paths))
			list_file(*paths, flags);
		paths++;
	}
	return (0);
}