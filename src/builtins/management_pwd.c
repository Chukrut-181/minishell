/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:09:43 by eandres           #+#    #+#             */
/*   Updated: 2024/11/12 13:50:12 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void management_pwd(void)
{
    char cwd[MAX_PATH];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd() error");
}

void update_pwd(t_mini *mini)
{
    char new_path[MAX_PATH];

    if (getcwd(new_path, sizeof(new_path)) != NULL)
    {
        set_env_var(mini, "OLDPWD", mini->full_path);
        set_env_var(mini, "PWD", new_path);
        free(mini->full_path);
        mini->full_path = strdup(new_path);
    }
    else
        perror("cd: error obteniendo el directorio actual");
}
