/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:44:42 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/28 10:42:59 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

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
char	**ft_process_input(char *line)
{
	char	**array;

	if (!line)
		return (NULL);
	if (ft_count_quotes(line) == -1)
	{
		printf("Warning: Unclosed quotes\n");
		return (NULL);
	}
	array = ft_split_prompt(line, ' ');
	if (!array)
	{
		printf("Error splitting input line\n");
		return (NULL);
	}
	free (line);
	array = ft_expand(array);
	array = ft_extract_operators(array, "<|>");
	array = ft_final_trim(array);
	return (array);
}

/**
 * main - Entry point for testing the input processing pipeline.
 *
 * This function repeatedly prompts the user for input, processes the input
 * using `process_input`, and prints each processed string in the resulting
 * array. Memory allocated for the input and the resulting array is freed
 * after each iteration.
 *
 * Return: Always returns 0 on success. Returns 1 if input processing fails.
 */
int	main(void)
{
	char	*test_line;
	char	**result;
	int		i;

	while (1)
	{
		test_line = readline("Parse this shit: ");
		result = ft_process_input(test_line);
		free(test_line);
		if (!result)
		{
			printf("Error: Unable to split the input string.\n");
			return (1);
		}
		i = 0;
		while (result[i])
		{
			printf("%s\n", result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	return (0);
}

/*

cc -Wall -Wextra -Werror -lreadline parse.c prompt_trim.c expand.c trim_quotes.c extract_operators.c free.c ../lib/libft/libft.a && ./a.out

<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >Outfile

*/