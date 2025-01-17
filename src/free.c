/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:08:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/01/17 11:36:37 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * free_array - Frees a dynamically allocated array of strings.
 *
 * This function iterates through a null-terminated array of strings,
 * deallocates each string, and sets its pointer to NULL. Finally,
 * it frees the array itself and sets the array pointer to NULL.
 *
 * **array: A double pointer to the dynamically allocated array of strings.
 *         Must be null-terminated. Passing NULL will have no effect.
 *
 * Notes:
 * - If the array is NULL, the function does nothing.
 * - Ensures that all pointers are set to NULL after deallocation.
 */
void ft_free_array(char **array)
{
	int i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	//free(array);
}

/*
 * ft_free_mini - Frees the memory allocated for a linked list of t_mini nodes
 *
 * This function iterates through a linked list of t_mini nodes, deallocates
 * the memory for each node's member variables, and frees the node itself.
 * It also calls the ft_free_array function to free any dynamically allocated
 * arrays (such as `full_cmd` and `envp`) associated with each node.
 *
 * **freethis: A pointer to the first node in the linked list to be freed.
 *             Each node in the list is of type t_mini. The linked list must
 *             be traversed until all nodes are freed.
 *
 * Notes:
 * - If the `freethis` pointer is NULL, the function does nothing.
 * - This function ensures that all dynamically allocated memory associated
 *   with the list is freed, preventing memory leaks.
 */
void ft_free_mini(t_mini *freethis)
{
	t_mini *aux;

	while (freethis)
	{
		if (freethis->full_cmd)
			ft_free_array(freethis->full_cmd);
		if (freethis->full_path)
			free(freethis->full_path);
		if (freethis->envp)
			ft_free_array(freethis->envp);
		if (freethis->command)
			free(freethis->command);
		aux = freethis;
		freethis = freethis->next;
		free(aux);
	}
}

void	ft_clean_and_reset(t_mini *mini)
{
	t_mini	*aux;

	if (mini->limit)
	{
		free(mini->limit);
		mini->limit = NULL;
	}
	if (mini->next != NULL)
	{
		aux = mini->next;
		ft_free_mini(aux);
	}
	reset_mini_state(mini);
}
