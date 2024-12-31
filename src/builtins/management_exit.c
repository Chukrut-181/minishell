/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:56:53 by eandres           #+#    #+#             */
/*   Updated: 2024/12/31 10:21:28 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static	void	bucle_free(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
} */

/*
Redirijo la gestión de todos los frees de salida al ejecutar exit 
a ft_free_mini. Evitamos redundancias: doublke free, invalid pointer, etc.
*/

int management_exit(t_mini *mini)
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
