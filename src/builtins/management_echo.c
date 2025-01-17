/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:41:37 by eandres           #+#    #+#             */
/*   Updated: 2025/01/17 14:17:15 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	management_echo(t_mini *mini)
{
	char	parameter;
	int		i;

	i = 1;
	parameter = 1;
	if (!mini->full_cmd[i])
		return (mini->status = 0);
	if (mini->full_cmd[i] && ft_strncmp(mini->full_cmd[i], "-n", 2) == 0)
	{
		parameter = 0;
		i++;
	}
	while (mini->full_cmd[i])
	{
		write(1, mini->full_cmd[i], ft_strlen(mini->full_cmd[i]));
		if (mini->full_cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (parameter == 1)
		write(1, "\n", 1);
	mini->status = 0;
	return (mini->status);
}
