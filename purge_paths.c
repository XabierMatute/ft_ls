/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:13:33 by xmatute-          #+#    #+#             */
/*   Updated: 2024/12/05 12:55:06 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int is_valid_path(char const *path)
{
	struct stat sb;

	if (stat(path, &sb) != -1)
		return (1);
	if (opendir(path))
		return (1);
	return (0);
}

char **purge_paths(char const **paths)
{
	char **purged_paths;
	int i = 0;
	int j = 0;

	purged_paths = save_calloc(ft_parrlen((void **)paths) + 1, sizeof(char *));
	while (paths[i])
	{
		if (!is_valid_path(paths[i]))
		{
			ft_eprintf("ft_ls: cannot access '%s': %s\n", paths[i], strerror(errno));
			i++;
			continue;
		}
		purged_paths[j] = ft_strdup(paths[i]);
		i++;
		j++;
	}
	purged_paths[j] = NULL;
	return (purged_paths);
}