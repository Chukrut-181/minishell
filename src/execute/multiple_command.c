/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:18 by eandres           #+#    #+#             */
/*   Updated: 2024/12/19 13:48:38 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_pipes(int pipefd[2], t_mini *mini)
{
	if (pipe(pipefd) == -1)
	{
		perror("Error creando el pipe");
		return (-1);
	}
	return (0);
}

void	pipe_outfile(int pipefd[2])
{
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("error en dup2");
		return ;
	}
	close(pipefd[1]);
}

void	pipe_infile(int pipefd[2], int last_fd)
{
	if (last_fd != STDIN_FILENO)
	{
		if (dup2(last_fd, STDIN_FILENO) == -1)
		{
			perror("error en dup2");
			return ;
		}
		close(last_fd);
	}
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

void	close_pipe(int pipefd[2], int last_fd)
{
	if (last_fd != STDIN_FILENO)
		close(pipefd);
	close(pipefd[1]);
}

void	handle_multiples_command(int pipefd[2], int last_fd, t_mini *mini)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("error en fork");
		return ;
	}
	else if (pid == 0)
	{
		pipe_outfile(pipefd);
		pipe_infile(pipefd, last_fd);
		handle_redirections(mini);
		execute_command(mini);
	}
}
