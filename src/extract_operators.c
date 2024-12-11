/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:58:58 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/10 15:13:21 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

/**
 * ft_concatenate_array - 	Merges a temporary array into an existing array at
 * 							a specific index.
 *
 * This function creates a new array by combining elements from an existing
 * array with those from a temporary array, inserting the temporary array at
 * the specified index. The original array is freed after its contents
 * are copied.
 *
 * **array: The original array of strings to merge into.
 * **temp_array: The temporary array of strings to be merged.
 * index: 	The position in the original array where the temporary array
 * 			is inserted.
 *
 * Return: 	A new null-terminated array containing the merged contents of
 * 			`array` and `temp_array`. Returns NULL if memory allocation fails.
 */
char	**ft_concatenate_array(char **array, char **temp_array, int index)
{
	char	**new_array;
	int		i;
	int		j;

	new_array = malloc(sizeof(char *) * (ft_arraylen(array) + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < index)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	j = 0;
	while (temp_array[j])
		new_array[i++] = ft_strdup(temp_array[j++]);
	while (array[index + 1])
	{
		new_array[i++] = ft_strdup(array[index + 1]);
		index++;
	}
	new_array[i] = NULL;
	ft_free_array(array);
	return (new_array);
}

/**
 * ft_arraylen - 	Calculates the number of elements in a
 * 					null-terminated array of strings.
 *
 * This function iterates through a null-terminated array of strings and
 * counts the number of elements. It safely handles a NULL pointer by
 * returning 0.
 *
 * **array: The input array of strings to evaluate.
 *
 * Return: The number of elements in the array. Returns 0 if the array is NULL.
 */
int	ft_arraylen(char **array)
{
	int	i;
	if (!array || !array[0])
		return (0);
	i = 0;
	while (array && array[i])
	{
		i++;
	}
	return (i);
}

/**
 * ft_extract_operators - 	Splits strings in an array based 
 * 							on operator positions.
 *
 * This function identifies strings in the array containing specified operators
 * (from the `operators` string) and splits them into separate array elements.
 * The resulting strings are properly integrated into the array.
 *
 * **array: The input array of strings to process.
 * *operators: A string containing the operator characters to extract.
 *
 * Return: A new array with operators extracted into separate elements.
 *         Returns NULL if the input array or operators string is NULL.
 */
char	**ft_extract_operators(char **array, const char *operators)
{
	char	**temp_array;
	int		i;

	i = 0;
	while (array && array[i])
	{
		if (ft_strchr(operators, array[i][0]) && array[i][1] != '\0')
		{
			temp_array = ft_create_temp_array(array, i, 1);
			array = ft_concatenate_array(array, temp_array, i);
			ft_free_array(temp_array);
		}
		else if (ft_strchr(operators, array[i][ft_strlen(array[i]) - 1])
			&& array[i][ft_strlen(array[i]) - 2])
		{
			temp_array = ft_create_temp_array(array, i,
					(ft_strlen(array[i]) - 1));
			array = ft_concatenate_array(array, temp_array, i);
			i++;
			ft_free_array(temp_array);
		}
		i++;
	}
	return (array);
}

/**
 * create_temp_array - 	Creates a temporary array by splitting a string
 * 						at a given position.
 *
 * This function generates a two-element array from a string,
 * where the first element contains the substring before the split point,
 * and the second element contains the characters after the split point.
 * The resulting array is null-terminated.
 *
 * **array: The original array containing the string to split.
 * i: The index of the string to split in the array.
 * j: The position in the string where the split occurs.
 *
 * Return: 	A null-terminated array of two strings.
 * 			Returns NULL if memory allocation fails.
 */
char	**ft_create_temp_array(char **array, int i, int j)
{
	char	**temp_array;

	temp_array = malloc(sizeof(char *) * 3);
	if (!temp_array)
	{
		return (NULL);
	}
	temp_array[0] = ft_substr(&array[i][0], 0, j);
	temp_array[1] = ft_strdup(&array[i][j]);
	temp_array[2] = NULL;
	return (temp_array);
}
