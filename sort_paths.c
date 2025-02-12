/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:06:50 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 19:32:37 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static time_t	get_mtime(const char *path, char *dir_path)
{
	struct stat file_stat;
	if (get_stat(path, dir_path, &file_stat))
		return 0;
	return (file_stat.st_mtime);
}

static char **sort_paths_t(char **files, char *dir_path)
{
	size_t	i = 0;

	while (files[i])
	{
		size_t	j = 0;
		while (files[j + 1 + i])
		{
			if (get_mtime(files[j], dir_path) < get_mtime(files[j + 1], dir_path))
				ft_swap_p((void *)&files[j], (void *)&files[j + 1]);
			j++;
		}
		i++;
	}
	return(files);
}

static char **sort_paths_a(char **files)
{
	size_t	i = 0;

	while (files[i])
	{
		size_t	j = 0;
		while (files[j + 1 + i])
		{
			if (ft_strncmp(files[j], files[j + 1], strlen(files[j]) + 1) > 0)
				ft_swap_p((void *)&files[j], (void *)&files[j + 1]);
			j++;
		}
		i++;
	}
	return(files);
}

char **sort_paths(char **files, const t_flags flags, char *dir_path)
{
	files = sort_paths_a(files);
	if (flags.t)
		return (sort_paths_t(files, dir_path));
	return (files);
}