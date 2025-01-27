/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:09:32 by igchurru          #+#    #+#             */
/*   Updated: 2025/01/27 11:04:21 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * ft_get_full_envp - Allocates and initializes a copy of the env variables.
 * @node: Pointer to the `t_mini` struct where the env vars will be stored.
 * @envp: Double-pointer to the original env vars passed to the program.
 * 
 * Description:
 * This function creates a full copy of the env vars and stores them in 
 * the `envp` field of the `t_mini` struct. It counts the number of env vars,
 * allocates memory for an array of strings, and iterates over each env var, 
 * delegating the copying process to the `ft_get_single_envp` function.
 * A pointer to the original `envp` array is stored in the `env_copy` field.
 * 
 * Steps:
 * 1. Counts the number of strings in the `envp` array (`env_count`).
 * 2. Allocates memory for an array of pointers.
 * 3. Checks if memory allocation succeeded; if not, logs an error
 *    using `perror` and exits.
 * 4. Iterates through `envp`, invoking `ft_get_single_envp`
 *    to duplicate each string.
 * 5. Sets the last pointer in the allocated array to `NULL`.
 * 6. Stores a pointer to the original `envp` in the
 *    `env_copy` field of `node`.
 */
void	ft_get_full_envp(t_mini *mini, char **envp)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (envp[count] != NULL)
		count++;
	mini->env_copy = malloc((count + 1) * sizeof(char *));
	if (mini->env_copy == NULL)
		return ;
	while (i < count)
	{
		mini->env_copy[i] = ft_strdup(envp[i]);
		if (mini->env_copy[i] == NULL)
		{
			error(mini, 1, "Could not copy env variables");
			return ;
		}
		i++;
	}
	mini->env_copy[count] = NULL;
}


void	ft_increment_shlvl(t_mini *mini)
{
	int	i;
	int	current_shlvl;

	i = 0;
	while (mini->env_copy[i])
	{
		if (ft_strncmp(mini->env_copy[i], "SHLVL=", 6) == 0)
		{
			current_shlvl = (ft_atoi(mini->env_copy[i] + 6));
			current_shlvl++;
			free(mini->env_copy[i]);
			mini->env_copy[i] = ft_strjoin("SHLVL=", ft_itoa(current_shlvl));
			break ;
		}
		else
			i++;
	}
}
