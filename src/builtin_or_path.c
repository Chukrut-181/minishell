/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:19:15 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/13 11:48:37 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_if_builtin(t_mini *node)
{
	if (!ft_strcmp(node->full_cmd[0], "echo"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_cmd[0], "cd"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_cmd[0], "pwd"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_cmd[0], "export"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_cmd[0], "unset"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_cmd[0], "env"))
		node->is_builtin = 1;
	else if (!ft_strcmp(node->full_cmd[0], "exit"))
		node->is_builtin = 1;
}

//he creado esta funcion para gestionar la posibilidad de que sea una ruta completa

static void check_this(t_mini *node)
{
	if (node->full_cmd[0][0] == '/' || node->full_cmd[0][0] == '.')
    {
        node->full_path = ft_strdup(node->full_cmd[0]);
        return ;
    }
}

void	ft_get_path(t_mini *node)
{
	char	**paths;
	char	*valid_path;
	int		i;

	check_this(node);
	if (node->is_builtin == 1)
	{
		node->full_path = NULL;
		return ;
	}
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	valid_path = NULL;
	while (paths[i])
	{
		valid_path = ft_strjoin(paths[i], "/");
		valid_path = ft_strjoin(valid_path, node->full_cmd[0]);
		if (access(valid_path, X_OK) == 0)
		{
			node->full_path = ft_strdup(valid_path);
			return ;
		}
		i++;
	}
}
