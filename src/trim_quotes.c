/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:51:34 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/13 11:49:31 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * count_quotes - 	Counts the number of quotes in a string and verifies
 * 					proper pairing.
 *
 * This function counts single (') and double (") quotes in the input string,
 * ensuring they are properly paired. Quotes within a context of the opposite
 * type are ignored (e.g., single quotes inside double quotes are treated
 * as literals).
 *
 * *s1: The input string to analyze.
 *
 * Return: The total number of valid quote characters in the string.
 *         Returns -1 if the quotes are improperly paired.
 */
int	ft_count_quotes(char const *s1)
{
	int		count;
	int		i;
	bool	dquote;
	bool	squote;

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (s1 && s1[i])
	{
		squote = (squote + (!dquote && s1[i] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !squote) || (s1[i] == '\'' && !dquote))
			count++;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (count);
}

/**
 * ft_strtrim_quotes - 	Removes quotes from a string while preserving
 * 						content integrity.
 *
 * This function removes single (') and double (") quotes from the
 * input string, ensuring that nested or paired quotes are handled
 * appropriately. Quotes are removed only if they are properly paired.
 * Unbalanced quotes result in a NULL return.
 *
 * *s1: The input string to trim.
 * squote: Indicates if a single-quote context is active (initially 0).
 * dquote: Indicates if a double-quote context is active (initially 0).
 *
 * Return: 	A newly allocated string with quotes removed,
 * 			or NULL on failure or unbalanced quotes.
 * 
 * The caller is responsible for freeing the returned string.
 */
char	*ft_strtrim_quotes(char const *s1, int squote, int dquote)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = ft_count_quotes(s1);
	if (!s1 || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s1) - count + 1));
	if (!trimmed)
		return (NULL);
	while (s1[i[0]])
	{
		squote = (squote + (!dquote && s1[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i[0]] == '\"')) % 2;
		if ((s1[i[0]] != '\"' || squote) && (s1[i[0]] != '\'' || dquote) \
			&& ++i[1] >= 0)
			trimmed[i[1]] = s1[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}

/**
 * get_quote_context - 	Determines the quote context at a given index
 * 						in a string.
 *
 * This function evaluates the state of quoting (single or double)
 * at the specified index of the string. It considers nested and paired
 * quotes to determine whether the current context is within quotes or not.
 *
 * *s: The input string to evaluate.
 * index: The index within the string to check for quote context.
 *
 * Return: The current quote context:
 *         - 0 if no quote is active.
 *         - '\'' if in a single-quote context.
 *         - '\"' if in a double-quote context.
 */
char	ft_get_quote_context(const char *s, int index)
{
	char		quote;
	const char	*aux;
	int			i;

	quote = 0;
	aux = s;
	i = 0;
	while (i < index)
	{
		if (aux[i] == '\'' || aux[i] == '\"')
		{
			if (quote == 0)
				quote = aux[i];
			else if (quote == aux[i])
				quote = 0;
		}
		i++;
	}
	return (quote);
}

/**
 * final_trim - Removes outermost matching quotes from each string in an array.
 *
 * This function iterates through an array of strings and removes the outermost
 * quotes (single or double) from each string if they are properly paired.
 * The trimmed strings are updated in place, and the original memory is freed.
 *
 * **array: The array of strings to trim.
 *
 * Return: The modified array with quotes removed, or NULL if **array is NULL.
 */
char	**ft_final_trim(char **array)
{
	int		i;
	char	*trimmed;
	int		len;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		len = ft_strlen(array[i]);
		if ((len > 1) && array[i][0] == array[i][len - 1])
		{
			if (array[i][0] == '\'' || array[i][0] == '\"')
			{
				trimmed = ft_substr(array[i], 1, (len - 2));
				free(array[i]);
				array[i] = trimmed;
			}
		}
		i++;
	}
	return (array);
}
