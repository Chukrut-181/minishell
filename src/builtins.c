/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:50:47 by eandres           #+#    #+#             */
/*   Updated: 2025/01/02 08:20:21 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int management_builtins(t_mini *mini)
{
    mini->full_path = ft_strdup(mini->full_cmd[0]);
    if (ft_strcmp(mini->full_cmd[0], "cd") == 0)
        mini->status = management_cd(mini);
    else if (ft_strcmp(mini->full_cmd[0], "pwd") == 0)
        mini->status = management_pwd(mini);
    else if (ft_strcmp(mini->full_cmd[0], "env") == 0)
        mini->status = management_env(mini);
    else if (ft_strcmp(mini->full_cmd[0], "unset") == 0)
        mini->status = management_unset(mini);
    else if (ft_strcmp(mini->full_cmd[0], "echo") == 0)
        mini->status = management_echo(mini);
    else if (ft_strcmp(mini->full_cmd[0], "export") == 0)
        mini->status = management_export(mini);
    else if (ft_strcmp(mini->full_cmd[0], "exit") == 0)
        mini->status = management_exit(mini);
    return (mini->status);
}
