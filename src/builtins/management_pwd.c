/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:09:43 by eandres           #+#    #+#             */
/*   Updated: 2025/01/31 09:44:12 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	management_pwd(t_mini *mini)
{
	char	cwd[MAX_PATH];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(mini->outfile, &cwd, ft_strlen(cwd));
		write(mini->outfile, "\n", 1);
		g_exit_status = 0;
	}
	else
	{
		perror("Error: pwd");
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
		perror("Error: pwd");
}
