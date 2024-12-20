/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:56:53 by eandres           #+#    #+#             */
/*   Updated: 2024/12/20 15:29:38 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static	void	bucle_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
} */

void	management_exit(t_mini *mini)
{
	(void)mini;
//	if (mini)
//	{
//		bucle_free(mini->full_cmd);
//		if (mini->full_path)
//			free(mini->full_path);
//		bucle_free(mini->env_copy);
//		free(mini);
//	}
	rl_clear_history();
	exit(0);
}
