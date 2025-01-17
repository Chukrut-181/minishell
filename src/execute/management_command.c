/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:05:06 by eandres           #+#    #+#             */
/*   Updated: 2025/01/17 16:51:27 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirection1(t_mini *mini)
{
	if (mini->infile != STDIN_FILENO)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
		{
			error(mini, 1, "error in dup2");
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
			error(mini, 1, "error in dup2");
			exit(EXIT_FAILURE);
		}
		close(mini->outfile);
	}
}

void	execute_external_command(t_mini *mini)
{
	if (execve(mini->full_path, mini->full_cmd, mini->envp) == -1)
	{
		error(mini, 127, "non executable");
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
		error(mini, 1, "error: fork");
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
