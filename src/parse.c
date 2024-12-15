/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:44:42 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/13 13:20:28 by eandres          ###   ########.fr       */
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
t_mini	*ft_process_input(char *line, char **envp)
{
	char	**array;
	t_mini	*mini;

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
	/* int i = 0;
	printf("\n");
	while (array && array[i])
	{
		printf("%s\n", array[i]);
		i++;
	} */
	mini = ft_create_structure(array, envp);
	ft_free_array(array);

	return (mini);
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
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	int res;
	char	*test_line;
	t_mini	*result;
	t_mini	*aux;

	while (1)
	{
		test_line = readline("\nParse this shit: ");
		result = ft_process_input(test_line, envp);
		if (!result)
		{
			printf("Error: Unable to split the input string.\n");
			return (1);
		}
		int	i = 1;
		res = management_builtins(result);
		if (res == 1)
			execute_external_command(result);
		while (result)
		{
			printf("\n***COMMAND Nº %i***\n", i);
			printf("In	fd: %i\n", result->infile);
			printf("Out	fd: %i\n", result->outfile);
			int	k = 0;
			while (result->full_cmd[k])
			{
				printf("full_cmd[%i]: %s\n", k, result->full_cmd[k]);
				k++;
			}
			printf("full_path: %s\n", result->full_path);
			printf("is_builtin: %i\n", result->is_builtin);
			aux = result;
			result = result->next;
			free(aux);
			i++;
		}
	}
	return (0);
}

/*

cc -Wall -Wextra -Werror -lreadline parse.c prompt_trim.c expand.c trim_quotes.c extract_operators.c free.c initialize.c envp.c builtin_or_path.c ../lib/libft/libft.a && ./a.out

<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >Outfile

*/