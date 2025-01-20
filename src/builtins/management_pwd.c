/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:09:43 by eandres           #+#    #+#             */
/*   Updated: 2025/01/20 13:48:39 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	management_pwd(t_mini *mini)
{
	char	cwd[MAX_PATH];

	(void)mini;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_exit_status = 0;
	}
	else
	{
		perror("error whith pwd");
		g_exit_status = 1;
	}
	return (g_exit_status);
}

void	update_pwd(t_mini *mini)
{
	char	new_path[MAX_PATH];

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
