/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:41:37 by eandres           #+#    #+#             */
/*   Updated: 2025/01/30 14:24:28 by igchurru         ###   ########.fr       */
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
		return (g_exit_status = 0);
	if (mini->full_cmd[i] && ft_strncmp(mini->full_cmd[i], "-n", 2) == 0)
	{
		parameter = 0;
		i++;
	}
	while (mini->full_cmd[i])
	{
		write(mini->outfile, mini->full_cmd[i], ft_strlen(mini->full_cmd[i]));
		if (mini->full_cmd[i + 1] != NULL)
			write(mini->outfile, " ", 1);
		i++;
	}
	if (parameter == 1)
		write(mini->outfile, "\n", 1);
	g_exit_status = 0;
	return (g_exit_status);
}
