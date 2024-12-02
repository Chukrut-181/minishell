/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:39:10 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/29 11:37:51 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

t_mini	*ft_initialize_mini_node(char **envp)
{
	t_mini	*new_node;

	new_node = malloc(sizeof(t_mini));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_mini));
	ft_get_full_envp(new_node, envp);
	new_node->infile = STDIN_FILENO;
	new_node->outfile = STDOUT_FILENO;
	return (new_node);
}
