/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:29:00 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 18:42:37 by xmatute-         ###   ########.fr       */
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

int recursive_ls(char **files, char *path, const t_flags flags)
{
    char **absolute_paths = make_absolute_paths(files, path);
    
    ft_ls((const char **)absolute_paths, flags);
    free2((void **)absolute_paths);
    return (0);
}

int list_directory(char *path, const t_flags flags)
{
	errno = 0;
	char **files = get_files(path, flags);

	if (!files || errno)
		return (errno);

	files = sort_paths(files, flags);
	if (flags.R)
        recursive_ls(files, path, flags);
	else
    	list_files(files, flags);

	free2((void **)files);
	return (0);
}

// void list_directory(const char *path, const t_flags flags)
// {
//     (void)flags;
//     ft_printf("listing: %s\n", path);
// }

int list_directories_r(char **paths, const t_flags flags)
{
    size_t i = 0;

    while (paths[i])
        i++;
    while (i--)
        if (isdir(paths[i]))
        {
            if (flags.R || ft_parrlen((void **)paths) > 1)
                ft_printf("%s:\n", paths[i]);
            list_directory(paths[i], flags);
        }
    return (0);
}

int list_directories(char **paths, const t_flags flags)
{
    if (flags.r)
    {
        return (list_directories_r(paths, flags));
    }
    size_t i = 0;
	while (paths[i])
	{
		if (isdir(paths[i]))
        {
            if (flags.R || ft_parrlen((void **)paths) > 1)
                ft_printf("%s:\n", paths[i]);
            list_directory(paths[i], flags);
        }
		i++;
	}
	return (0);
}