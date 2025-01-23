/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:05:06 by eandres           #+#    #+#             */
/*   Updated: 2025/01/23 10:46:04 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirection1(t_mini *mini)
{
	if (mini->infile != STDIN_FILENO)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
		{
			error(mini, 1, "Dup2 error: Input redirection failed");
			exit(EXIT_FAILURE);
		}
		close(mini->infile);
	}
}

void	handle_redirection2(t_mini *mini)
{
	if (mini->outfile != STDOUT_FILENO)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
		{
			error(mini, 1, "Dup2 error: Output redirection failed");
			exit(EXIT_FAILURE);
		}
		close(mini->outfile);
	}
}

void	execute_external_command(t_mini *mini)
{
	if (execve(mini->full_path, mini->full_cmd, mini->envp) == -1)
	{
		error(mini, 127, "Command not found");
		exit(EXIT_FAILURE);
	}
}

void	execute_one_command(t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		error(mini, 1, "Fork error: Cannot execute child process");
		return ;
	}
	else if (pid == 0)
	{
		handle_redirection1(mini);
		handle_redirection2(mini);
		execute_external_command(mini);
	}
	else
	{
		if (mini->infile != STDIN_FILENO)
			close(mini->infile);
		if (mini->outfile != STDOUT_FILENO)
			close(mini->outfile);
		waitpid(pid, &status, 0);
		update_exit_status(status);
	}
}
