/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:41:00 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 20:29:18 by xmatute-         ###   ########.fr       */
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
void    *save_calloc(size_t nmemb, size_t size);

char    **sort_paths(char **files, const t_flags flags, char *dir_path);
int     list_paths(char **paths, const t_flags flags, char *dir_path);
int     list_files(char **paths, const t_flags flags, char *dir_path);
int     list_only_files(char **paths, const t_flags flags, char *dir_path);
int     list_directories(char **paths, const t_flags flags, char *dir_path);
int     isdir(const char *path, char *dir_path);
void    put_file(const char *path, const t_flags flags, char *dir_path);

typedef int (*valid_file_func)(const char *);
int     not_ocult(const char *path);
int     not_dot(const char *path);
int     not_dot_not_ocult(const char *path);
int     all_files(const char *path);

char    **get_files(const char *path, char *dir_path, valid_file_func valid_file);

char    *make_absolute_path(const char *dir_path, const char *file_name);
int    get_stat(const char *path, char *dir_path, struct stat *stat);

void    save_closedir(const char *path, DIR *dir);

#ifndef DEBUG
#define DEBUG 0
#endif // DEBUG

#endif //FT_LS_H
