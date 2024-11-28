/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:08:48 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/28 10:30:15 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

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
