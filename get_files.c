/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:32:26 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/13 11:51:43 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int not_ocult(const char *path)
{
	return (path[0] != '.');
}

int all_files(const char *path)
{
	(void)path;
	return (1);
}

int not_dot(const char *path)
{
	return (ft_strncmp(path, ".", 2) != 0 && ft_strncmp(path, "..", 3) != 0);
}

int not_dot_not_ocult(const char *path)
{
	return (not_dot(path) && not_ocult(path));
}

size_t	count_files(const char *path, valid_file_func valid_file)
{
	size_t	i = 0;
	DIR		*dir = opendir(path);
	struct dirent	*file;

	if (!dir)
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return (0);
	}
	errno = 0;
	while ((file = readdir(dir)))
	{
		errno = 0;
		if (valid_file(file->d_name))
			i++;
	}
	save_closedir(path, dir);
	if (errno)
		ft_eprintf("ft_ls: error reading '%s': %s\n", path, strerror(errno));
	return (i);
}

static char **get_files_from(const char *path, valid_file_func valid_file)
{
	DIR				*dir = opendir(path);
	struct dirent 	*file = NULL;
	char			**files = save_calloc(count_files(path, valid_file) + 1, sizeof(char *));
	size_t			i = 0;

	if (errno)
		return (NULL);
	if (!dir)
	{
		ft_eprintf("(get_files)ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return(NULL);
	}
	errno = 0;
	while ((file = readdir(dir)))
	{
		errno = 0;
		if (valid_file(file->d_name))
			files[i++] = ft_strdup(file->d_name);
	}
	save_closedir(path, dir);
	if (errno)
		ft_eprintf("ft_ls: error reading '%s': %s\n", path, strerror(errno));
	files[i] = NULL;
	return (files);
}

char **get_files(const char *path, char *dir_path, valid_file_func valid_file)
{
	char *absolute_path = make_absolute_path(dir_path, path);
	char **files = get_files_from(absolute_path, valid_file);

	free(absolute_path);
	return (files);
}