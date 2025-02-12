/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:32:26 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/21 19:54:42 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	count_files(const char *path, const t_flags flags)
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
		if (file->d_name[0] != '.' || flags.a)
			i++;
	}
	save_closedir(path, dir);
	if (errno)
		ft_eprintf("ft_ls: error reading '%s': %s\n", path, strerror(errno));
	return (i);
}

char **get_files(const char *path, const t_flags flags)
{
	DIR				*dir = opendir(path);
	struct dirent 	*file = NULL;
	char			**files = save_calloc(count_files(path, flags) + 1, sizeof(char *));
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
		if (file->d_name[0] != '.' || flags.a)
			files[i++] = ft_strdup(file->d_name);
	}
	save_closedir(path, dir);
	if (errno)
		ft_eprintf("ft_ls: error reading '%s': %s\n", path, strerror(errno));
	files[i] = NULL;
	return (files);
}