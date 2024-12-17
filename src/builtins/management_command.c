/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:05:06 by eandres           #+#    #+#             */
/*   Updated: 2024/12/17 13:53:06 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirections(t_mini *mini)
{
	printf("%d\n", mini->infile);
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
//	char	*cmd_path;

	pid = fork();
	if (pid == -1)
	{
		perror("error: fork");
		return ;
	}
	else if (pid == 0)
	{
		//handle_redirections(mini);
		//cmd_path = get_path(mini);
		if (execve(mini->full_path, mini->full_cmd, mini->envp) == -1)
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

void	process_command(t_mini *mini)
{
	int		result;

	//handle_redirections(mini);
	result = management_builtins(mini);
	if (result == 1)
		execute_external_command(mini);
	free_args(mini->full_cmd);
	mini->full_cmd = NULL;
}
