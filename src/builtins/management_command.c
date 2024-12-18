/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:05:06 by eandres           #+#    #+#             */
/*   Updated: 2024/12/18 11:21:31 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirections(t_mini *mini)
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

static void	handle_command(t_mini *mini)
{
	int sig;

	if (mini->is_builtin == 1)
	{
		sig = management_builtins(mini);
		exit(sig);
	}
	else
	{
		execute_external_command(mini);
		exit(1);
	}
}

void	execute_external_command(t_mini *mini)
{
	if (execve(mini->full_path, mini->full_cmd, mini->envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	process_command(t_mini *mini)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid == 0)
	{
		handle_redirections(mini);
		handle_command(mini);
	}
}
