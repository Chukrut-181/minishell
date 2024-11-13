/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:41:37 by eandres           #+#    #+#             */
/*   Updated: 2024/11/12 16:27:59 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	management_echo(t_mini *mini)
{
	char parameter;
	int i;

	i = 1;
	parameter = 1;
	if (mini->full_cmd[i] && ft_strncmp(mini->full_cmd[i], "-n", 2) == 0)
	{
		parameter = 0;
		i++;
	}
	while (mini->full_cmd[i])
	{
		write(1, mini->full_cmd[i], ft_strlen(mini->full_cmd[i]));
		i++;
	}
	if (parameter == 1)
		write(1, "\n", 1);
}
