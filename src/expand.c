/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:57:34 by igchurru          #+#    #+#             */
/*   Updated: 2025/01/09 14:22:50 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * expand_path - Expands a tilde (~) in a string to the user's home directory.
 *
 * If the string begins with a tilde and is not quoted, this function replaces
 * it with the value of the "HOME" environment variable. If "HOME" is not set,
 * an empty string is used instead. The rest of the string remains unchanged.
 *
 * *word: The input string to be expanded.
 * index: The current index within the string, used to check quoting context.
 *
 * Return: A newly allocated string with the expanded path, or NULL on failure.
 *         The caller is responsible for freeing the returned string.
 */
char	*ft_expand_path(char *word)
{
	const char	*home_dir;
	char		*expanded;

	if (word[0] != '~')
		return (ft_strdup(word));
	home_dir = getenv("HOME");
	if (!home_dir)
		home_dir = "";
	expanded = malloc(ft_strlen(home_dir) + ft_strlen(word));
	if (!expanded)
		return (NULL);
	ft_strlcpy(expanded, home_dir, (ft_strlen(home_dir) + 1));
	ft_strlcat(expanded, word + 1, (ft_strlen(expanded) + ft_strlen(word)));
	return (expanded);
}

static char *get_env_value(t_mini *mini, const char *name)
{
    int i;
    int len;

    len = ft_strlen(name);
	i = 0;
    while (mini->env_copy[i])
    {
        if (ft_strncmp(mini->env_copy[i], name, len) == 0 && mini->env_copy[i][len] == '=')
        {
            return (mini->env_copy[i] + len + 1);
        }
		i++;
    }
    return (NULL);
}

/**
 * expand_variable - Expands an environment variable within a string.
 *
 * This function identifies an env variable preceded by a dollar sign ($)
 * and replaces it with its value from the env. If the variable is quoted
 * by single quotes, it is not expanded. If the variable does not exist in
 * the env, it is replaced with an empty string. Any remaining portion of
 * the string after the variable is preserved.
 *
 * *word: The input string containing the variable.
 * index: The current index of the dollar sign in the string.
 *
 * Return: 	A newly allocated string with the expanded variable,
 * 			or NULL	on failure. 
 * 
 * The caller is responsible for freeing the returned string.
 */
char	*ft_expand_variable(t_mini *mini, char *word, int index)
{
	char	*var_name;
	int		name_len;
	char	*var_value;
	char	*expanded;

	name_len = ft_get_var_name_len(&word[index + 1]);
	var_name = ft_substr(&word[index + 1], 0, name_len);
	var_value = get_env_value(mini, var_name);
	if (!var_value)
		var_value = "";
	free(var_name);
	expanded = malloc(ft_strlen(var_value) + 1);
	if (!expanded)
		return (NULL);
	ft_strlcpy(expanded, var_value, (ft_strlen(var_value) + 1));
	if (word[index + name_len + 1] != '\0')
	{
		var_value = &word[index + name_len + 1];
		expanded = ft_strjoin(expanded, var_value);
	}
	return (expanded);
}

/**
 * get_var_name_len - Determines the length of a valid env variable name.
 *
 * Env variable names can contain alphanumeric characters and underscores.
 * This function calculates the length of the variable name starting from
 * the given string position.
 *
 * *var_name: The string starting with the variable name.
 *
 * Return: The length of the variable name.
 */
int	ft_get_var_name_len(const char *var_name)
{
	int	len;

	len = 0;
	while (*var_name && (ft_isalnum(*var_name) || *var_name == '_'))
	{
		len++;
		var_name++;
	}
	return (len);
}

/**
 * expand - Expands all env variables and tilde characters
 * 			in an array of strings.
 *
 * This function iterates through an array of strings, expanding each
 * string that begins with a tilde (~) to the user's home directory
 * and expanding variables prefixed by a dollar sign ($) to their
 * corresponding values in the environment.
 *
 * **temp: An array of strings to be expanded.
 *
 * Return: 	The array with expanded strings. If a string is replaced,
 * 			its original memory is freed. Returns NULL if `temp` is NULL.
 */
char	**ft_expand(t_mini *mini, char **temp)
{
	int		i;
	int		j;
	char	*prefix;

	i = 0;
	while (temp && temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][0] == '~')
				temp[i] = ft_expand_path(temp[i]);
			else if (temp[i][j] == '$'
				&& ft_get_quote_context(temp[i], j) != '\'')
			{
				prefix = ft_substr(temp[i], 0, j);
				temp[i] = ft_strjoin(prefix, ft_expand_variable(mini, temp[i], j));
				free(prefix);
			}
			j++;
		}
		i++;
	}
	return (temp);
}
