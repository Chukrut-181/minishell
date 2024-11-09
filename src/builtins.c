/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:50:47 by eandres           #+#    #+#             */
/*   Updated: 2024/11/09 08:05:51 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int management_builtins(t_mini *mini)
{
    if (ft_strcmp(mini->full_cmd[0], "cd") == 0)
        management_cd(mini);
    else if (ft_strcmp(mini->full_cmd[0], "pwd") == 0)
        management_pwd();
    else if (ft_strcmp(mini->full_cmd[0], "env") == 0)
        management_env(mini);
    else if (ft_strcmp(mini->full_cmd[0], "unset") == 0)
        management_unset(mini);
    else
        return (1);
    return (0);
}

void management_cd(t_mini *mini)
{
    char *home;

    if (mini->full_cmd[1] == NULL || (ft_strcmp(mini->full_cmd[1], "$HOME") == 0))
    {
        home = my_getenvp("HOME", mini->env_copy);
        if (!home || chdir(home) != 0)
            perror("cd: error al cambiar al directorio HOME");
    }
    else if (chdir(mini->full_cmd[1]) != 0)
    {
        perror("cd: error");
        return;
    }
    update_pwd(mini);
}

void update_pwd(t_mini *mini)
{
    char new_path[MAX_PATH];

    if (getcwd(new_path, sizeof(new_path)) != NULL)
    {
        my_setenv("OLDPWD", mini->full_path, 1, mini);
        my_setenv("PWD", new_path, 1, mini);
        free(mini->full_path);
        mini->full_path = strdup(new_path);
    }
    else
        perror("cd: error obteniendo el directorio actual");
}

void management_pwd(void)
{
    char cwd[MAX_PATH];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd() error");
}

void management_env(t_mini *mini)
{
    int i = 0;
    
    if (!mini->env_copy)
    {
        fprintf(stderr, "Error: Environment variables not available\n");
        return;
    }
    
    while (mini->env_copy[i])
    {
        printf("%s\n", mini->env_copy[i]);
        i++;
    }
}
