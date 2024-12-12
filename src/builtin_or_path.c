/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:19:15 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/12 11:27:20 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

void	ft_check_if_builtin(t_mini *node)
{
	if (!ft_strcmp(node->full_path, "echo"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_path, "cd"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_path, "pwd"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_path, "export"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_path, "unset"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_path, "env"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_path, "exit"))
		node->is_builtin = 1;
}

/* void	ft_get_path()
{

} */
