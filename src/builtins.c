/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:50:47 by eandres           #+#    #+#             */
/*   Updated: 2024/11/07 15:45:33 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	management_builtins(t_mini *mini)
{
	if (ft_strncmp(mini->full_cmd[0], "cd", 2))
		management_cd(mini);
	else if (ft_strcnmp(mini->full_cmd[0], "pwd", 3))
		management_pwd(mini);
	/* else if (ft_strcnmp(mini->full_cmd[0], "echo", 4))
		management_echo(mini);
	else if (ft_strcnmp(mini->full_cmd[0], "env", 3))
		management_env(mini);
	else if (ft_strcnmp(mini->full_cmd[0], "export", 6))
		management_export(mini);
	else if (ft_strcnmp(mini->full_cmd[0], "unset", 5))
		management_unset(mini); */
	return (0);
}

void    management_cd(t_mini *mini)
{
    char    *home;
	char	*oldpwd;

    if (mini->full_cmd[1] == NULL || (ft_strcmp(mini->full_cmd[1], "$HOME") == 0))
    {
        home = my_getenv("HOME", "error al cambiar al directorio");
        if (chdir(home) != 0)
            perror("cd: error al cambiar al directorio HOME");
    }
    else if (strcmp(mini->full_cmd[1], "-") == 0)
    {
        oldpwd = my_getenv("OLDPWD", "error al conseguir el oldpwd");
        if (chdir(oldpwd) != 0)
            perror("cd: error al cambiar al directorio anterior");
        else
            printf("%s\n", oldpwd);
    }
    else if(chdir(mini->full_cmd[1]) != 0)
    {
        perror("error");
        return;
    }
	update_pwd(mini);
}

void	update_pwd(t_mini *mini)
{
	char    new_path[MAX_PATH];

	if (getcwd(new_path, sizeof(new_path)) != NULL)
	{
		// tengo que modificar la funcion setenv por export
		// setenv actualiza una variable del env
		setenv("OLDPWD", mini->full_path, 1);
        setenv("PWD", new_path, 1);
        free(mini->full_path);
        mini->full_path = strdup(new_path);
	}
	else
		perror("cd: error obteniendo el directorio actual");
}
