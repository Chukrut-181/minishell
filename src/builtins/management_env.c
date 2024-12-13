/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:11:50 by eandres           #+#    #+#             */
/*   Updated: 2024/11/27 16:16:05 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	management_env(t_mini *mini)
{
	int	i;

	i = 0;
	if (!mini->env_copy)
	{
		fprintf(stderr, "Error: Environment variables not available\n");
		return ;
	}
	while (mini->env_copy[i])
	{
		printf("%s\n", mini->env_copy[i]);
		i++;
	}
}
