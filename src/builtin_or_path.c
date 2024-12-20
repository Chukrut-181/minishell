/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:19:15 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/20 09:20:12 by igchurru         ###   ########.fr       */
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

void	ft_get_path(t_mini *node)
{
	char	**paths;
	char	*temp_path;
	char	*valid_path;
	int		i;

	if (node->is_builtin == 1)
		return ;
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		valid_path = ft_strjoin(temp_path, node->full_cmd[0]);
		free(temp_path);
		if (access(valid_path, X_OK) == 0)
		{
			node->full_path = valid_path;
			ft_free_array(paths);
			return ;
		}
		i++;
	}
	ft_free_array(paths);
}
