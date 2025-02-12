/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:45:28 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 14:01:57 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include "t_flags.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>

int ft_ls(char **path, const t_flags flags);

#endif // MAIN_H
