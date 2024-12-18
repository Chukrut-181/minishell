/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:12:40 by eandres           #+#    #+#             */
/*   Updated: 2024/12/18 11:34:18 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	management_cd(t_mini *mini)
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
