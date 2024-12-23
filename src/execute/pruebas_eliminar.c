#include "../../include/minishell.h"

/* void handle_multiples_command(int pipefd[2], int last_fd, t_mini *mini, t_prompt *cmd)
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
} */

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
        if (next_cmd)
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

t_prompt *create_prompt(void)
{
    t_prompt *new;

    new = (t_prompt *)malloc(sizeof(t_prompt));
    if (!new)
        return (NULL);
    new->cmds = NULL;
    new->next = NULL;
    return (new);
}

void parse_command(t_prompt *prompt, const char *command)
{
    char *cmd_copy = strdup(command);
    char *token = strtok(cmd_copy, "|");
    
    while (token != NULL)
    {
        // Eliminar espacios al inicio y al final del token
        while (*token == ' ') token++;
        char *end = token + strlen(token) - 1;
        while (end > token && *end == ' ') end--;
        *(end + 1) = 0;

        // Crear un nuevo nodo de lista con el comando
        t_list *new_cmd = ft_lstnew(strdup(token));
        if (new_cmd)
            ft_lstadd_back(&(prompt->cmds), new_cmd);

        token = strtok(NULL, "|");
    }
    free(cmd_copy);
}
