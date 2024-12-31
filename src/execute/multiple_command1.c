/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:18 by eandres           #+#    #+#             */
/*   Updated: 2024/12/30 14:07:56 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_multiples_command(int pipefd[2], int last_fd, t_mini *mini, t_mini *next_cmd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        // Handle input from previous command if exists
        pipe_input(last_fd);
        // Handle output to next command if exists
        if (next_cmd)
            pipe_output(pipefd);
        // Handle any redirections specific to this command
        handle_redirection1(mini);
        handle_redirection2(mini);
        if (mini->is_builtin)
            management_builtins(mini);
        else
            execute_external_command(mini);
        exit(EXIT_SUCCESS);
    }
    mini->pid = pid;
}

void execute_multiples_command(t_mini *mini)
{
    int     last_fd;
    int     pipefd[2];
    int     status;
    t_mini  *current;

    last_fd = STDIN_FILENO;
    current = mini;
    while (current)
    {
        // Create pipe for all but the last command
        if (current->next)
        {
            waitpid(mini->pid, &status, 0);
            if (create_pipes(pipefd) == -1)
                return ;
        }
   		handle_multiples_command(pipefd, last_fd, current, current->next);
        // Close used pipe ends and update for next iteration
        close_pipe(pipefd, last_fd);
        if (current->next)
            last_fd = pipefd[0];
        current = current->next;
    }
    while (waitpid(-1, &status, 0) > 0)
        continue ;
}

void process_command2(t_mini *mini)
{
    if (mini->is_builtin)
    {
        mini->status = management_builtins(mini);
        // Actualiza el código de salida de la shell si es necesario
        // Por ejemplo: shell.last_exit_status = status;
    }
    else if (mini->next == NULL)
    {
        execute_one_command(mini);
    }
    else
    {
        execute_multiples_command(mini);
    }
}
