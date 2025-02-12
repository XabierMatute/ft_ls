/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_calloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:57:23 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/21 16:57:41 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*save_calloc(size_t nmemb, size_t size)
{
	void *mem;

	if (!(mem = ft_calloc(nmemb, size)))
	{
		ft_eprintf("ft_ls: cannot allocate memory for %i * %i: %s\n", nmemb, size, strerror(errno));
		exit(errno);
	}
	return (mem);
}