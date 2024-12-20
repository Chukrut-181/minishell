/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:05:06 by eandres           #+#    #+#             */
/*   Updated: 2024/12/20 15:44:15 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirection1(t_mini *mini)
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
}

void	handle_redirection2(t_mini *mini)
{
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
	if (execve(mini->full_path, mini->full_cmd, mini->envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	execute_one_command(t_mini *mini)
{
	pid_t pid;
	int status;
	
	pid = fork();
	if (pid == -1)
	{
		perror("erro: fork");
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
	}
}

void	execute_multiples_command(t_mini *mini)
{
	int		last_fd;
	int		pipefd[2];
	int		status;
	int 	i = 0;

	last_fd = STDIN_FILENO;
	while (mini->full_cmd[i])
	{
		write(1, "estoy2\n", 7);
		//crear pipes siempre que exista un comando mas adelante
		if (mini->next)
		{
			if (create_pipes(pipefd) == -1)
				return ;
		}
		//despues ejecutar lo que diga el comando gestionando redirecciones
		handle_multiples_command(pipefd, last_fd, mini);
		//despues cerrar el pipe que se ha creado.
		close_pipe(pipefd, last_fd);
		mini->next = mini->next->next;
		last_fd = pipefd[0];
	}
	while(wait(&status) > 0)
		mini->num = WEXITSTATUS(status);
}

void	process_command2(t_mini *mini)
{
	if (mini->next == NULL && mini->is_builtin == 1)
	{
		management_builtins(mini);
		return ;
	}
	else if (mini->next == NULL)
		execute_one_command(mini);
	else
	{
		write(1, "estoy1\n", 7);
		execute_multiples_command(mini);
	}
}
