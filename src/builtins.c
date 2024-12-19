/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:50:47 by eandres           #+#    #+#             */
/*   Updated: 2024/12/18 10:43:43 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	management_builtins(t_mini *mini)
{
	if (ft_strcmp(mini->full_cmd[0], "cd") == 0)
		management_cd(mini);
	else if (ft_strcmp(mini->full_cmd[0], "pwd") == 0)
		management_pwd();
	else if (ft_strcmp(mini->full_cmd[0], "env") == 0)
		management_env(mini);
	else if (ft_strcmp(mini->full_cmd[0], "unset") == 0)
		management_unset(mini);
	else if (ft_strcmp(mini->full_cmd[0], "echo") == 0)
		management_echo(mini);
	else if (ft_strcmp(mini->full_cmd[0], "export") == 0)
		management_export(mini);
	else if (ft_strcmp(mini->full_cmd[0], "exit") == 0)
		management_exit(mini);
	return (1);
}
