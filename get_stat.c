/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:06:13 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 19:23:45 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int get_stat(const char *path, char *dir_path, struct stat *stat)
{
    char *absolute_path = make_absolute_path(dir_path, path);
    int r = lstat(absolute_path, stat);

    if (r)
        ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
    free(absolute_path);
    return r;
}

