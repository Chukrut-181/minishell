/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:09:32 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/13 13:20:53 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_get_full_envp(t_mini *node, char **envp)
{
	int	i;
	int	env_count;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	node->envp = malloc(sizeof(char *) * (env_count + 1));
	if (!node->envp)
	{
		perror("malloc failed for env_vars\n");
		return ;
	}
	i = 0;
	while (i < env_count)
	{
		node->envp[i] = malloc(sizeof(char) * (ft_strlen(envp[i])) + 1);
		if (!node->envp[i])
		{
			perror("malloc failed for env_vars[i]\n");
			ft_free_array(node->envp);
			return ;
		}
		ft_strlcpy(node->envp[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	node->envp[i] = NULL;
	node->env_copy = node->envp;
}
