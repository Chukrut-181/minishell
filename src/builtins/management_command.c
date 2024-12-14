/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:05:06 by eandres           #+#    #+#             */
/*   Updated: 2024/12/14 08:13:48 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_redirections(t_mini *mini)
{
	if (mini->infile != STDIN_FILENO)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(mini->infile);
	}
	if (mini->outfile != STDOUT_FILENO)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(mini->outfile);
	}
}

void	execute_external_command(t_mini *mini)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
	{
		perror("error: fork");
		return ;
	}
	else if (pid == 0)
	{
		handle_redirections(mini);
		cmd_path = get_path(mini);
		if (execve(cmd_path, mini->full_cmd, mini->envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

//	checkear estas 2 funciones porque creo que no es necesaria ya que esto la haces en el parseo
//  esto lo cree yo para hacer pruebas y que funcionase todo.
//  IMPORTANTE: revisar.

int	process_command(t_mini *mini, char *line)
{
	char	**args;
	int		result;

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

char	*get_path(t_mini *mini)
{
	int		i;
	char	*new_env;
	char	**allpath;
	char	*path;
	char	*new_path;

	i = 0;
	new_env = getenv("PATH");
	if (!new_env)
		return (ft_strdup(mini->full_cmd[0]));
	allpath = ft_split(new_env, ':');
	if (!allpath)
		return (ft_strdup(mini->full_cmd[0]));
	while (allpath[i])
	{
		path = ft_strjoin(allpath[i], "/");
		new_path = ft_strjoin(path, mini->full_cmd[0]);
		free(path);
		if (access(new_path, F_OK | X_OK) == 0)
		{
			ft_free(allpath);
			return (new_path);
		}
		free(new_path);
		i++;
	}
	ft_free(allpath);
	return (ft_strdup(mini->full_cmd[0]));
}
