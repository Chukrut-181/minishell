/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:56:53 by eandres           #+#    #+#             */
/*   Updated: 2025/01/10 18:09:39 by eandres          ###   ########.fr       */
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
	ft_free_mini(mini);
	rl_clear_history();
	exit(0);
}
