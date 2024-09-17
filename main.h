/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:45:28 by xmatute-          #+#    #+#             */
/*   Updated: 2024/09/17 23:36:41 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include "t_flags.h"
#include "libft.h"

int ft_ls(const char *path, const t_flags flags);

void NewFunction(DIR *dir, const t_flags flags);

#endif // MAIN_H
