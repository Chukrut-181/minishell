/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:10:25 by eandres           #+#    #+#             */
/*   Updated: 2024/11/27 17:54:43 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	find_and_remove_var(char **env, const char *var_name)
{
	int	j;
	int	len;

	j = -1;
	len = count_val(var_name);
	while (env[++j])
	{
		if (ft_strncmp(var_name, env[j], len) == 0 && env[j][len] == '=')
		{
			free(env[j]);
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			return (1);
		}
	}
	return (0);
}

int	count_val(const char *val)
{
	int	i;

	i = 0;
	while (val[i] && val[i] != '=')
	{
		i++;
	}
	return (i);
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (-1);
}

char	**create_env_copy(char **env)
{
	int		i;
	int		len;
	char	**env_copy;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	env_copy = malloc(sizeof(char *) * (len + 1));
	if (!env_copy)
		return (NULL);
	while (i < len)
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
		{
			while (i > 0)
				free(env_copy[--i]);
			free(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[len] = (NULL);
	return (env_copy);
}

void	management_unset(t_mini *mini)
{
	int	i;

	i = 1;
	if (!mini->env_copy || (is_valid(mini->full_cmd[1]) == 0))
		perror("uset: invalid arguments\n");
	while (mini->full_cmd[i])
	{
		if (!find_and_remove_var(mini->env_copy, mini->full_cmd[i]))
			perror("uset: valiable not found\n");
		i++;
	}
}

/* void management_unset(t_mini *mini)
{
	int i, j;
	int len;
	int found;

	i = 1;
	if (!mini->env_copy || (is_valid(mini->full_cmd[1]) == 0))
	{
		fprintf(stderr, "unset: invalid arguments\n");
		return;
	}
	while (mini->full_cmd[i])
	{
		len = count_val(mini->full_cmd[i]);
		j = -1;
		found = 0;
		while (mini->env_copy[j++])
		{
			if (ft_strncmp(mini->full_cmd[i], mini->env_copy[j], len) == 0 && mini->env_copy[j][len] == '=')
			{
				free(mini->env_copy[j]);
				while (mini->env_copy[j++])
					mini->env_copy[j] = mini->env_copy[j + 1];
				found = 1;
				break;
			}
		}
		if (!found)
			fprintf(stderr, "unset: %s: variable not found\n", mini->full_cmd[i]);
		i++;
	}
} */
