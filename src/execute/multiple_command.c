/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:18 by eandres           #+#    #+#             */
/*   Updated: 2024/12/21 12:59:55 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* int	create_pipes(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("Error creando el pipe");
		return (-1);
	}
	return (0);
} */

void	pipe_output(int pipefd[2], t_prompt *cmd)
{
	if (cmd->next != NULL)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("error en dup2");
			return ;
		}
		write(1, "estoy6\n", 7);
		close(pipefd[1]);
	}
}

void	pipe_input(int last_fd)
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

/* void	close_pipe(int pipefd[2], int last_fd)
{
	if (last_fd != STDIN_FILENO)
		close(pipefd[0]);
	close(pipefd[1]);
} */

/* void	handle_multiples_command(int pipefd[2], int last_fd, t_mini *mini, t_prompt *cmd)
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
		write(1, "estoy4\n", 7);
		pipe_input(last_fd);
		if (cmd->next)
			pipe_output(pipefd, cmd);
		handle_redirection1(mini);
		handle_redirection2(mini);
		execute_command(mini);
	}
}
 */