/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:56:53 by eandres           #+#    #+#             */
/*   Updated: 2024/12/20 10:06:00 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Esta función resulta innecesaria y la comento: Tenemos fr_free_mini
que ya libera toda la lista de comandos t_mini y sus respectivos arrays 
y strings.
*/
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
void	management_exit(t_mini *mini)
{
	if (mini)
	{
		ft_free_mini(mini);
/* 		bucle_free(mini->full_cmd);
		if (mini->full_path)
			free(mini->full_path);
		bucle_free(mini->env_copy);
		free(mini); */
	}
	rl_clear_history();
	exit(0);
}
