/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:18 by eandres           #+#    #+#             */
/*   Updated: 2025/01/23 10:52:01 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_pipes(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("Could not create pipe");
		return (EXIT_FAILURE);
	}
	return (0);
}

void	pipe_output(int pipefd[2])
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("Dup2 error: Output redirection failed");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
}

void	pipe_input(int last_fd)
{
	if (last_fd != STDIN_FILENO)
	{
		if (dup2(last_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 error: Input redirection failed");
			exit(EXIT_FAILURE);
		}
		close(last_fd);
	}
}

void	close_pipe(int pipefd[2], int last_fd)
{
	if (last_fd != STDIN_FILENO)
		close(last_fd);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
}

void	execute_command(t_mini *mini)
{
	if (mini->is_builtin == 1)
	{
		management_builtins(mini);
		exit(1);
	}
	else
	{
		execute_external_command(mini);
		exit(0);
	}
}
