/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:06:50 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/13 15:43:50 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// static time_t	get_mtime(const char *path, char *dir_path)
// {
// 	struct stat file_stat;
// 	if (get_stat(path, dir_path, &file_stat))
// 		return 0;
// 	// return (file_stat.st_mtim.tv_nsec);
// 	return (file_stat.st_mtime);
// }

static struct timespec get_timespec(const char *path, char *dir_path)
{
	struct stat file_stat;
	if (get_stat(path, dir_path, &file_stat))
		return (struct timespec){0, 0};
	return (file_stat.st_mtim);
}

static int is_newer(const char *path1, const char *path2, char *dir_path)
{
	struct timespec mtime1 = get_timespec(path1, dir_path);
	struct timespec mtime2 = get_timespec(path2, dir_path);

	if (mtime1.tv_sec == mtime2.tv_sec)
		return (mtime1.tv_nsec > mtime2.tv_nsec);
	return (mtime1.tv_sec > mtime2.tv_sec);
}

static char **sort_paths_t(char **files, char *dir_path)
{
	size_t	i = 0;

	while (files[i])
	{
		size_t	j = 0;
		while (files[j + 1 + i])
		{
			if (is_newer(files[j + 1], files[j], dir_path))
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