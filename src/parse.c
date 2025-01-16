/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:44:42 by igchurru          #+#    #+#             */
/*   Updated: 2025/01/16 10:52:27 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * process_input - Parses and processes a command line input string.
 *
 * This function performs several steps to parse and process the input:
 * 1. Checks for unclosed quotes in the input line using `count_quotes`.
 *    If unclosed quotes are found, a warning is printed, and NULL is returned.
 * 2. Splits the input string into an array of words using `ft_split_prompt`.
 * 3. Expands environment variables and paths using `expand`.
 * 4. Extracts and separates operators `<`, `|`, and `>`
 *	  using `ft_extract_operators`.
 * 5. Removes surrounding quotes from words using `final_trim`.
 *
 * *line: The input string to be parsed and processed.
 *
 * Return: A null-terminated array of processed strings. NULL on error.
 */
t_mini	*ft_process_input(t_mini *mini, char *line, char **envp)
{
	char	**array;

	if (!line)
		return (NULL);
	if (ft_count_quotes(line) == -1)
	{
		printf("Warning: Unclosed quotes\n");
		ft_free_mini(mini);
		return (NULL);
	}
	array = ft_split_prompt(line, ' ');
	if (!array || array == NULL)
	{
		printf("Error splitting input line\n");
		ft_free_mini(mini);
		return (NULL);
	}
	array = ft_expand(mini, array);
	array = ft_extract_operators(array, "<|>");
	array = ft_final_trim(array);
	mini = ft_create_structure(mini, array, envp);
	ft_free_array(array);
	return (mini);
}
