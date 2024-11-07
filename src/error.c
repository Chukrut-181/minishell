/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:22:23 by eandres           #+#    #+#             */
/*   Updated: 2024/11/07 12:26:59 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*my_getenv(char *str, char *error)
{
	char *home;

	home = getenv(str);
	if (!home)
	{
		perror(error);
		return NULL;
	}
	return (home);
}
