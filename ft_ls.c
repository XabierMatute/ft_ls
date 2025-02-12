/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:33 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 13:53:56 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char **default_paths(void)
{
	char **paths;

	paths = save_calloc(2, sizeof(char *));
	paths[0] = ft_strdup(".");
	paths[1] = NULL;
	return (paths);
}

static int default_ls(const t_flags flags)
{
	char	**paths;

	paths = default_paths();
	ft_ls((const char **)paths, flags);
	free2((void **)paths);
	return (0);
}

int ft_ls(char const **paths, const t_flags flags)
{
	if (ft_parrlen((void **)paths) == 0)
		return (default_ls(flags));
	
	char **purged_paths = purge_paths(paths);
	list_paths(purged_paths, flags);
	free2((void **)purged_paths);
	return (0);
}
