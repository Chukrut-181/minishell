/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:08:48 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/19 12:46:24 by igchurru         ###   ########.fr       */
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
void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

t_mini	*ft_free_mini(t_mini *freethis)
{
	t_mini	*aux;

	while (freethis)
	{
		if (freethis->full_cmd)
			ft_free_array(freethis->full_cmd);
		if (freethis->full_path)
			free(freethis->full_path);
		if (freethis->envp)
			ft_free_array(freethis->envp);
/* 		if (freethis->env_copy)
			ft_free_array(freethis->env_copy); */
		aux = freethis;
		freethis = freethis->next;
		free(aux);
	}
	return (NULL);
}
