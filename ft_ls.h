/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:41:00 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 13:25:15 by xmatute-         ###   ########.fr       */
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
#include <sys/sysmacros.h>

int 	ft_ls(char const**path, const t_flags flags);
char **purge_paths(char const **paths);
void *save_calloc(size_t nmemb, size_t size);

char **sort_paths(char **files, const t_flags flags);
int	list_paths(char **paths, const t_flags flags);
int list_files(char **paths, const t_flags flags);
int list_only_files(char **paths, const t_flags flags);
int list_directories(char **paths, const t_flags flags);
int isdir(const char *path);
void put_file(const char *path, const t_flags flags);
char **get_files(const char *path, const t_flags flags);
void save_closedir(const char *path, DIR *dir);

#ifndef DEBUG
#define DEBUG 0
#endif // DEBUG

#endif //FT_LS_H
