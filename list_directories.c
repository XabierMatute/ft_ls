/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:29:00 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/13 12:52:40 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *make_absolute_path(const char *dir_path, const char *file_name)
{
	if (!dir_path || !dir_path[0])
		return  (ft_strdup(file_name));
	
	char *tmp = ft_strjoin(dir_path, "/");
	if (!tmp)
	{
		ft_eprintf("ft_ls: cannot allocate memory for %s/%s: %s\n", dir_path, file_name, strerror(errno));
		exit(errno);
	}	
	char *path = ft_strjoin(tmp, file_name);
	if (!path)
	{
		ft_eprintf("ft_ls: cannot allocate memory for %s/%s: %s\n", dir_path, file_name, strerror(errno));
		exit(errno);
	}
	free(tmp);
	return path;
}

char **make_absolute_paths(char **files, const char *dir_path)
{
    size_t i = 0;
    while (files[i])
    {
        files[i] = make_absolute_path(dir_path, files[i]);
        i++;
    }
    return files;
}

int recursive_ls(char *path, const t_flags flags, char *dir_path)
{
	errno = 0;
	valid_file_func valid_file = not_dot;
	if (!flags.a)
		valid_file = not_dot_not_ocult;
	char **files = get_files(path, dir_path, valid_file);
	char *absolute_path = make_absolute_path(dir_path, path);

	if (!files || errno)
		return (errno);

	files = sort_paths(files, flags, absolute_path);

   	list_directories(files, flags, absolute_path);

	free2((void **)files);
	free(absolute_path);
	return (0);
}

// int list_directory(char *path, const t_flags flags, char *dir_path)
// {
// 	errno = 0;
// 	valid_file_func valid_file = all_files;
// 	if (!flags.a)
// 		valid_file = not_ocult;
// 	if (flags.R)
// 		valid_file = not_dot;
// 	if (flags.R && !flags.a)
// 		valid_file = not_dot_not_ocult;
// 	char **files = get_files(path, dir_path, valid_file);
// 	char *absolute_path = make_absolute_path(dir_path, path);

// 	if (!files || errno)
// 		return (errno);

// 	files = sort_paths(files, flags, absolute_path);
// 	if (flags.R)
//         recursive_ls(files, flags, absolute_path);
// 	else
//     	list_files(files, flags, absolute_path);

// 	free2((void **)files);
// 	free(absolute_path);
// 	return (0);
// }

int list_directory(char *path, const t_flags flags, char *dir_path)
{
	errno = 0;
	valid_file_func valid_file = all_files;
	if (!flags.a)
		valid_file = not_ocult;
	char **files = get_files(path, dir_path, valid_file);

	if (!files || errno)
		return (errno);

	char *absolute_path = make_absolute_path(dir_path, path);

	files = sort_paths(files, flags, absolute_path);

   	list_files(files, flags, absolute_path);
	ft_putchar('\n');

	free2((void **)files);
	free(absolute_path);
	if (flags.R)
        recursive_ls(path, flags, dir_path);
	return (0);
}

int is_only_one_dir(char **paths, t_flags flags)
{
	return !(flags.R || ft_parrlen((void **)paths) > 1);
}

int list_directories_r(char **paths, const t_flags flags, char *dir_path)
{
    size_t i = 0;

    while (paths[i])
        i++;
    while (i--)
        if (isdir(paths[i], dir_path))
        {
            if (!is_only_one_dir(paths, flags))
			{
				char *absolute_path = make_absolute_path(dir_path, paths[i]);
                ft_printf("%s:\n", absolute_path);
				free(absolute_path);
			}
            list_directory(paths[i], flags, dir_path);
        }
    return (0);
}

int list_directories(char **paths, const t_flags flags, char *dir_path)
{
    if (flags.r)
        return (list_directories_r(paths, flags, dir_path));
    size_t i = 0;
	while (paths[i])
	{
		if (isdir(paths[i], dir_path))
        {
            if (!is_only_one_dir(paths, flags))
			{
				char *absolute_path = make_absolute_path(dir_path, paths[i]);
                ft_printf("%s:\n", absolute_path);
				free(absolute_path);
			}
            list_directory(paths[i], flags, dir_path);
        }
		i++;
	}
	return (0);
}