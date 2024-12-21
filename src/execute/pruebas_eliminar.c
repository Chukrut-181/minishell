#include "../../include/minishell.h"

void handle_multiples_command(int pipefd[2], int last_fd, t_mini *mini, t_prompt *cmd)
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
        if (last_fd != STDIN_FILENO)
        {
            if (dup2(last_fd, STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(last_fd);
        }

        // Handle output to next command if exists
        if (cmd->next)
        {
            close(pipefd[0]);  // Close read end
            if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(pipefd[1]);
        }

        // Handle any redirections specific to this command
        handle_redirection1(mini);
        handle_redirection2(mini);

        // Execute the command
        if (mini->is_builtin)
            management_builtins(mini);
        else
            execute_external_command(mini);
        exit(EXIT_SUCCESS);
    }
    mini->pid = pid;
}

void close_pipe(int pipefd[2], int last_fd)
{
    if (last_fd != STDIN_FILENO)
        close(last_fd);
    if (pipefd[1] != STDOUT_FILENO)
        close(pipefd[1]);
}

int create_pipes(int pipefd[2])
{
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    return (0);
}
