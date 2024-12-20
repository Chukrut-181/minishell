/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:19:15 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/20 11:57:57 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * ft_check_if_builtin - Checks if the command is a built-in command.
 *
 * This function cheks the first argument of the command (node->full_cmd[0])
 * against a list of built-in commands. If a match is found, the `is_builtin`
 * field of the node is set to 1, indicating it's a built-in command.
 *
 * **node: A pointer to the t_mini structure, which holds the command
 * to be checked.
 */
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

/*
 * ft_get_path - Searches for a command in the directories specified in the
 * PATH environment variable.
 * This function attempts to find the full path of a command by checking
 * each directory listed in the PATH environment variable. If the command is 
 * found and is executable, the full path is assigned to the node's 
 * `full_path` member.
 * 
 * **node: A pointer to the t_mini structure, which represents a command. 
 *         and the `full_path` field which will be populated with the
 * 		   full path to the executable if found.
 *
 * Function flow:
 * 1. It first checks if the command is a built-in (node->is_builtin == 1).
 *    If it is, the function returns immediately as built-in commands do
 *    	not require path searching.
 * 2. If the command is not a built-in, it retrieves the PATH environment
 *    variable and splits it into individual directories.
 * 3. It then iterates through each directory in the PATH variable and attempts
 * 	  to build the full path to the executable by concatenating the directory
 *    with the command name.
 * 4. For each directory, it checks if the resulting path is executable
 *    using `access(valid_path, X_OK)`. If an executable file is found, the
 *    `full_path` field of the node is set to the full path of the executable.
 * 5. If no valid path is found after checking all directories, the `full_path` remains unchanged.
 * 6. Memory for the temporary strings (`temp_path` and `valid_path`) and the split `paths` array is properly
 *    freed at the end of the function to avoid memory leaks.
 *
 * Notes:
 * - If the `PATH` environment variable is not set, `ft_split` will return NULL, which should be handled
 *   elsewhere in the program to avoid segmentation faults.
 * - If the `full_cmd` in the node contains a relative or absolute path, this function will not be used, as
 *   it's assumed that the user has already provided the full path.
 *
 * Possible improvements:
 * - Additional error handling could be added for cases where `getenv("PATH")` returns NULL or if any
 *   system calls (like `access`) fail unexpectedly.
 */
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
			node->full_path = ft_strdup(valid_path);
			free(valid_path);
			ft_free_array(paths);
			return ;
		}
		free(valid_path);
		i++;
	}
	ft_free_array(paths);
}
