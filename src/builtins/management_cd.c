/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:12:40 by eandres           #+#    #+#             */
/*   Updated: 2024/12/30 14:49:06 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_env_value(char **envp, char *var_name)
{
	int	i;
	int	len;

	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
 		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

static void	update_env_variable(char **envp, char *var_name, char *new_value)
{
	int		i;
	int		len;
	char	*new_entry;

	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			new_entry = ft_strjoin(var_name, "=");
			envp[i] = ft_strjoin(new_entry, new_value);
			free(new_entry);
			return ;
		}
		i++;
	}
}

static char	*get_target_dir(t_mini *mini)
{
	if (mini->full_cmd[1])
		return (mini->full_cmd[1]);
	return (get_env_value(mini->envp, "HOME"));
}

static void	update_pwd_variables(char *oldpwd, t_mini *mini)
{
	char	cwd[MAX_PATH];

	update_env_variable(mini->envp, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_variable(mini->envp, "PWD", cwd);
}

int	management_cd(t_mini *mini)
{
	char	cwd[MAX_PATH];
	char	*oldpwd;
	char	*target_dir;

	oldpwd = getcwd(cwd, sizeof(cwd));
	target_dir = get_target_dir(mini);
	if (!target_dir)
	{
		perror("hola");
		mini->status = 1;
		return (mini->status);
	}
	if (chdir(target_dir) == -1)
	{
		perror("hola");
		mini->status = 1;
		return (mini->status);
	}
	update_pwd_variables(oldpwd, mini);
	mini->status = 0;
	return (mini->status);
}

/* char	*my_getenvp(const char *name, char **env_copy)
{
	int	i;
	int	len;

	if (!name || !env_copy)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env_copy[i])
	{
		if (ft_strncmp(env_copy[i], name, len) == 0 && env_copy[i][len] == '=')
			return (&env_copy[i][len + 1]);
		i++;
	}
	return (NULL);
} */

/* void	management_cd(t_mini *mini)
{
	if (mini->full_cmd[1] == NULL)
	{
		if (chdir(mini->full_cmd[1]) != 0)
			perror("cd: error al cambiar al directorio HOME");
	}
	else if (chdir(mini->full_cmd[1]) != 0)
	{
		perror("cd: error");
		return ;
	}
	update_pwd(mini);
} */
