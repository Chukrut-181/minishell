/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:07:30 by eandres           #+#    #+#             */
/*   Updated: 2025/01/17 15:40:15 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	error(t_mini *mini, int sig, char *str)
{
	mini->status = sig;
	ft_free_mini(mini);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
