/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:05:06 by eandres           #+#    #+#             */
/*   Updated: 2024/11/18 14:21:10 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void execute_external_command(t_mini *mini)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		//Proceso hijo
		char *cmd_path = get_path(mini);
		if (execve(cmd_path, mini->full_cmd, mini->envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		//Proceso padre
		waitpid(pid, &status, 0);
	}
}

int process_command(t_mini *mini, char *line)
{
	char **args;
	int result;

	args = ft_split(line, ' ');
	if (!args)
		return (0);
	mini->full_cmd = args;
	result = management_builtins(mini);
	if (result == 1)
		execute_external_command(mini);
	free_args(mini->full_cmd);
	mini->full_cmd = NULL;
	return (result);
}

char *get_path(t_mini *mini)
{
	int i;
	char *new_env;
	char **allpath;
	char *path;
	char *new_path;

	i = 0;
	new_env = getenv("PATH");
	if (!new_env)
		return ft_strdup(mini->full_cmd[0]);

	allpath = ft_split(new_env, ':');
	if (!allpath)
		return ft_strdup(mini->full_cmd[0]);

	while (allpath[i])
	{
		path = ft_strjoin(allpath[i], "/");
		new_path = ft_strjoin(path, mini->full_cmd[0]);
		free(path);
		if (access(new_path, F_OK | X_OK) == 0)
		{
			ft_free(allpath);
			return new_path;
		}
		free(new_path);
		i++;
	}
	ft_free(allpath);
	return ft_strdup(mini->full_cmd[0]);
}
