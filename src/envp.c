/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:09:32 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/02 09:56:58 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

void ft_get_full_envp(t_mini *node, char **envp)
{
    int i;
    int env_count;

	env_count = 0;
    while (envp[env_count])
        env_count++;
    node->env_vars = malloc(sizeof(char *) * (env_count + 1));
    if (!node->env_vars)
    {
        perror("malloc failed for env_vars");
        return;
    }
    i = 0;
    while (i < env_count)
    {
        node->env_vars[i] = malloc(sizeof(char) * (ft_strlen(envp[i])) + 1);
        if (!node->env_vars[i])
        {
            perror("malloc failed for env_vars[i]");
            while (i > 0)
                free(node->env_vars[--i]);
            free(node->env_vars);
            return;
        }
        ft_strlcpy(node->env_vars[i], envp[i], ft_strlen(envp[i]) + 1);
        i++;
    }
    node->env_vars[i] = NULL;
}

