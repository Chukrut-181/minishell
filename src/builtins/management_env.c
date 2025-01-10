/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:11:50 by eandres           #+#    #+#             */
/*   Updated: 2024/12/30 14:07:23 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	management_env(t_mini *mini)
{
	int	i;

	i = 0;
	if (!mini->env_copy)
	{
		mini->status = 1;
		return (mini->status);
	}
	while (mini->env_copy[i])
	{
		printf("%s\n", mini->env_copy[i]);
		i++;
	}
	mini->status = 0;
	return (mini->status);
}
