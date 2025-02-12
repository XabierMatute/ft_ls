/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:06:50 by xmatute-          #+#    #+#             */
/*   Updated: 2024/12/05 13:41:18 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static time_t	get_mtime(const char *path)
{
	struct stat file_stat;
	if (lstat(path, &file_stat))
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return 0;
	}
	return (file_stat.st_mtime);
}

static char **sort_paths_t(char **files)
{
	size_t	i = 0;

	while (files[i])
	{
		size_t	j = 0;
		while (files[j + 1 + i])
		{
			if (get_mtime(files[j]) < get_mtime(files[j + 1]))
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

char **sort_paths(char **files, const t_flags flags)
{
	files = sort_paths_a(files);
	if (flags.t)
		return (sort_paths_t(files));
	return (files);
}