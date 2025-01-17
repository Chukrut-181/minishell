/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:06:14 by eandres           #+#    #+#             */
/*   Updated: 2025/01/17 11:53:22 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char	*create_env_var(const char *name, const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

static	int	find_env_var(char **env_copy, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env_copy[i])
	{
		if (ft_strncmp(env_copy[i], name, len) == 0 && env_copy[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void ft_free_env(char **var, int size)
{
	int i;

	if (!var)
		return ;
	i = 0;
	while (i < size)
	{
		if (var[i])
			free(var[i]);
		var[i] = NULL;
		i++;
	}
	free(var);
	var = NULL;
	return ;
}

static int add_new_env_var(t_mini *mini, const char *new_var)
{
	int     i;
	char    **new_env_copy;

	i = 0;
	while (mini->env_copy[i])
		i++;
	new_env_copy = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env_copy)
		return (-1);
	i = 0;
	while (mini->env_copy[i])
	{
		new_env_copy[i] = ft_strdup(mini->env_copy[i]);
		i++;
	}
	new_env_copy[i] = ft_strdup(new_var);
	if (!new_env_copy[i])
	{
		ft_free_array(new_env_copy);
		return (-1);
	}
	new_env_copy[i + 1] = NULL;
	ft_free_env(mini->env_copy, i);
	mini->env_copy = NULL;
	mini->env_copy = new_env_copy;
	return (0);
}

int	set_env_var(t_mini *mini, const char *name, const char *value)
{
	int		index;
	char	*new_var;

	if (!name || !mini->env_copy)
		return (-1);
	index = find_env_var(mini->env_copy, name);
	new_var = create_env_var(name, value);
	if (!new_var)
		return (-1);
	if (index >= 0)
	{
		free(mini->env_copy[index]);
		mini->env_copy[index] = NULL;
		mini->env_copy[index] = ft_strdup(new_var);
	}
	else
	{
		if (add_new_env_var(mini, new_var) < 0)
		{
			free(new_var);
			return (-1);
		}
	}
	free(new_var);
	return (0);
}

int	management_export(t_mini *mini)
{
	char	*value;

	if ((is_valid(mini->full_cmd[1]) == -1) || !mini->env_copy)
		return (perror("not found"), -1);
	value = ft_strchr(mini->full_cmd[1], '=');
	if (value)
	{
		*value = '\0';
		value++;
	}
	else
	{
		value = "";
	}
	return (set_env_var(mini, mini->full_cmd[1], value));
}
