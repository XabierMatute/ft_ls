/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:31:32 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 19:40:27 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int isdir(const char *path, char *dir_path)
{
    struct stat file_stat;

    if (get_stat(path, dir_path, &file_stat))
        return (0);
    return (S_ISDIR(file_stat.st_mode));
}
