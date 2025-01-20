/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:07:30 by eandres           #+#    #+#             */
/*   Updated: 2025/01/20 14:32:35 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error(t_mini *mini, int sig, char *str)
{
	(void)mini;
	g_exit_status = sig;
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
