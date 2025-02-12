/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_closedir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:55:19 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/21 19:55:37 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void save_closedir(const char *path, DIR *dir)
{
	if (closedir(dir))
	{
		ft_eprintf("ft_ls: cannot close '%s': %s\n", path, strerror(errno));
		exit(errno);
	}
}