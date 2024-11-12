/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:10:25 by eandres           #+#    #+#             */
/*   Updated: 2024/11/11 11:14:48 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int count_val(const char *val)
{
	int i = 0;
	while (val[i] && val[i] != '=')
	{
		i++;
	}
	return i;
}

char **create_env_copy(char **env)
{
	int i = 0;
	int len = 0;
	char **env_copy;

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

void management_unset(t_mini *mini)
{
	int i, j, k;
	int len;

	i = 1;
	j = 0;
	if (!mini->env_copy || !mini->full_cmd[1])
	{
		fprintf(stderr, "unset: invalid arguments\n");
		return;
	}
	while (mini->full_cmd[i])
	{
		len = count_val(mini->full_cmd[i]);
		while (mini->env_copy[j])
		{
			if (ft_strncmp(mini->full_cmd[i], mini->env_copy[j], len) == 0 && mini->env_copy[j][len] == '=')
			{
				free(mini->env_copy[j]);
				k = j;
				while (mini->env_copy[k])
				{
					mini->env_copy[k] = mini->env_copy[k + 1];
					k++;
				}
				break;
			}
			j++;
		}
		i++;
	}
}
