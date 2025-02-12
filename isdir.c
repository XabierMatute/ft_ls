/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:31:32 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/21 17:34:03 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int isdir(const char *path)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == -1)
    {
        ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
        return (0);
    }
    return (S_ISDIR(file_stat.st_mode));
}
