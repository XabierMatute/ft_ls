/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:41:00 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/10 11:45:07 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_LS_H
#define FT_LS_H

#include "t_flags.h"
#include "libft.h"
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

int ft_ls(const char *path, const t_flags flags);

#endif //FT_LS_H
