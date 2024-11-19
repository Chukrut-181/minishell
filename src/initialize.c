/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:01:45 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/19 15:25:06 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_mini	*initialize_mini(char **env)
{
	t_mini *mini;
	
	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		perror("Error: Could not allocate memory for mini\n");
		return (NULL);
	}
	mini->full_cmd = NULL;
	mini->full_path = getcwd(NULL, 0);
	mini->envp = env;
	mini->env_copy = create_env_copy(env);
	if (!mini->env_copy)
	{
		perror("Error: Could not create a copy of env vars\n");
		free(mini);
		return (NULL);
	}
	mini->is_builtins = 0;
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	return (mini);
}
