/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:11:50 by eandres           #+#    #+#             */
/*   Updated: 2025/01/31 09:52:43 by igchurru         ###   ########.fr       */
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
		write(mini->outfile, mini->env_copy[i], ft_strlen(mini->env_copy[i]));
		write(mini->outfile, "\n", 1);
		i++;
	}
	g_exit_status = 0;
	return (g_exit_status);
}
