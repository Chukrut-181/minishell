/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:07:30 by eandres           #+#    #+#             */
/*   Updated: 2025/01/22 10:11:17 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_exit_status = 0;

void	error(t_mini *mini, int sig, char *str)
{
	(void)mini;
	g_exit_status = sig;
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
