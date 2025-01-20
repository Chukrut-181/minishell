/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:11:50 by eandres           #+#    #+#             */
/*   Updated: 2025/01/20 13:48:11 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	management_env(t_mini *mini)
{
	int	i;

	i = 0;
	if (!mini->env_copy)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	while (mini->env_copy[i])
	{
		printf("%s\n", mini->env_copy[i]);
		i++;
	}
	g_exit_status = 0;
	return (g_exit_status);
}
