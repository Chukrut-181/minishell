/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:14:17 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/13 11:49:26 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * handle_quotes - Skips characters enclosed within quotes in a string.
 *
 * This function starts from the given index in the string, increments
 * the index until the matching closing quote is found or the string ends.
 * If a matching quote is found, it returns the index after the closing quote.
 * Otherwise, it returns the current index.
 *
 * *s: The input string.
 * i: The current index in the string.
 * quote: The type of quote to handle (single quote `'` or double quote `"`).
 *
 * Return: The index after the closing quote, or the current index
 * if no closing quote is found.
 */
static size_t	ft_handle_quotes(const char *s, size_t i, char quote)
{
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		return (i + 1);
	else
		return (i);
}

/**
 * ft_nb_words - Counts the number of words in a string,
 * considering delimiters and quotes.
 *
 * Words are sequences of characters separated by a specified delimiter.
 * Quoted sections (enclosed by single or double quotes) are treated as
 * part of a single word.
 *
 * *s: The input string.
 * c: The delimiter character.
 *
 * Return: The number of words in the string.
 */
static size_t	ft_nb_words(char const *s, char c)
{
	size_t	i;
	size_t	nb_words;

	if (!s[0])
		return (0);
	i = 0;
	nb_words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = ft_handle_quotes(s, i, s[i]);
		else if (s[i] == c)
		{
			nb_words++;
			while (s[i] && s[i] == c)
				i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		nb_words++;
	return (nb_words);
}

/**
 * ft_get_next_word - Extracts the next word in a string.
 *
 * This function updates the pointer to the next word and
 * calculates its length. Words are delimited by a specified character.
 * Quoted sections are treated as part of a single word and are skipped.
 *
 * **next_word: A pointer to the string pointer that holds the current
 * 				position in the string. It is updated to point to the
 * 				start of the next word.
 * *next_word_len: A pointer to store the length of the next word.
 * c: The delimiter character.
 */
static void	ft_get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;
	char	quote;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i])
	{
		if ((*next_word)[i] == '\'' || (*next_word)[i] == '\"')
		{
			quote = (*next_word)[i];
			i++;
			while ((*next_word)[i] && (*next_word)[i] != quote)
				i++;
			if ((*next_word)[i] == quote)
				i++;
		}
		else if ((*next_word)[i] == c)
			break ;
		else
			i++;
	}
	*next_word_len = i;
}

/**
 * ft_split_prompt - Splits a string into an array of words,
 * 					handling delimiters and quotes.
 *
 * This function allocates and returns an array of words derived from the
 * input string. Words are separated by the specified delimiter, and
 * quoted sections are treated as part of a single word.
 * Quoted words retain their content but do not include the quotes.
 *
 * *s: The input string to split. If NULL, the function returns NULL.
 * c: The delimiter character.
 *
 * Return: 	A null-terminated array of strings,
 * 			or NULL if allocation fails or the input string is NULL.
 */
char	**ft_split_prompt(char const *s, char c)
{
	char	**array;
	char	*next_word;
	size_t	next_word_len;
	size_t	i;

	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (ft_nb_words(s, c) + 1));
	if (!array)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < ft_nb_words(s, c))
	{
		ft_get_next_word(&next_word, &next_word_len, c);
		array[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		ft_strlcpy(array[i], next_word, next_word_len + 1);
		i++;
	}
	array[i] = NULL;
	return (array);
}
