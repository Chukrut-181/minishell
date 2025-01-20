/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:56:53 by eandres           #+#    #+#             */
/*   Updated: 2025/01/19 17:53:50 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Redirijo la gestión de todos los frees de salida al ejecutar exit 
a ft_free_mini. Evitamos redundancias: doublke free, invalid pointer, etc.
*/

int	management_exit(t_mini *mini)
{
	int	status;

	status = mini->status;
	ft_free_mini(mini);
	rl_clear_history();
	exit(status);
}
