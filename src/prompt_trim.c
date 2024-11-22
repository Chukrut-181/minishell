/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:14:17 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/22 11:18:30 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//#include <readline/readline.h>

/* Helper function to handle quoted sections.
Skips over characters within single or double quotes.
Parameters:
	- s: the input string.
	- i: current index in the string.
	- quote: the type of quote being handled (' or ").
Returns: The index after the closing quote or the end of the string
if no closing quote exists. */
static size_t	handle_quotes(const char *s, size_t i, char quote)
{
	i++;	// Move past the opening quote.
	while (s[i] && s[i] != quote)	// Keep iterating until the closing quote or the end of the string.
		i++;
	return (s[i] == quote ? i + 1 : i);	// Include the closing quote if present.
}

static char	**ft_malloc_error(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

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
		if (s[i] == '\'' || s[i] == '\"')	// Start of a quoted section.
			i = handle_quotes(s, i, s[i]);	// Skip over the quoted section.
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
		if ((*next_word)[i] == '\'' || (*next_word)[i] == '\"')	// Quoted section.
		{
			quote = (*next_word)[i];
			i++;	// Move past the opening quote.
			while ((*next_word)[i] && (*next_word)[i] != quote)	// Skip inside the quotes.
				i++;
			if ((*next_word)[i] == quote)	// Include the closing quote if present.
				i++;
		}
		else if ((*next_word)[i] == c)
			break ;
		else
			i++;
	}
	*next_word_len = i;
}

char	**ft_split_prompt(char const *s, char c)
{
	char	**tab;
	char	*next_word;
	size_t	next_word_len;
	size_t	i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_nb_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < ft_nb_words(s, c))
	{
		ft_get_next_word(&next_word, &next_word_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_word, next_word_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int main(void)
{
	char	*test_line;
	int		i;

	test_line = readline("input text: ");

    char **result = ft_split_prompt(test_line, ' ');
	free(test_line);
    if (!result)
    {
        printf("Error: Unable to split the input string.\n");
        return (1);
    }
	i = 0;
    while (result[i])
    {
        printf("Word %d: %s\n", i, result[i]);
        free(result[i]);
		i++;
    }
	printf("Word %d: %s\n", i, result[i]);
    free(result);
    return (0);
}

//	cc -Wall -Wextra -Werror -lreadline prompt_trim.c ../lib/libft/libft.a

//	string: echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
//	output: {echo, "hello      there", how, are, 'you 'doing?, $USER, |wc, -l, >outfile, NULL}

