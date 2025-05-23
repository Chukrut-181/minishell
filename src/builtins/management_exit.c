/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:56:53 by eandres           #+#    #+#             */
/*   Updated: 2025/01/20 14:33:55 by eandres          ###   ########.fr       */
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

	status = g_exit_status;
	ft_free_mini(mini);
	rl_clear_history();
	exit(status);
}
