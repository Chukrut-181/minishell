/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:23:07 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/05 13:14:11 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Initialize the head of the token linked list to NULL
// Create a buffer to temporarily store characters of each token
// Set up indices for iterating over 'line' and the buffer
// Variable to track if we are inside a quote. This is set to '"' or '\'' if inside quotes, otherwise '\0'
// Main loop: Iterate through each character of the input line
	// Case 1: Handle spaces outside of quotes (indicates the end of a token)
			// Check if there is any text in the buffer to create a token
			// Null-terminate the buffer
			// Add the buffer as a token to the list
			// Reset buffer index for the next token
	// Case 2: Handle quote characters (either double " or single ')
			// Check if we're already inside a quote
			// Start of a quote, store the quote character
			// End of the current quote, reset quote to '\0'
			// Add character to buffer if inside quotes
	// Case 3: Handle operators (|, >, <) outside of quotes
			// If there are characters in the buffer, finalize and add the current token
			// Add the operator itself as a separate token
			// Null-terminate the operator string
	// Case 4: Normal character, add to the current buffer
	// Move to the next character in the line
// After the loop, check if there’s any remaining token in the buffer
	// Null-terminate the buffer
	// Add the final token to the list
// Return the head of the linked list containing all tokens
t_token	*tokenize(char *line)
{
	t_token	*head;
	char	buffer[1024];
	int		i;
	int		buf_index;
	char	quote;

	head = NULL;
	i = 0;
	buf_index = 0;
	quote = '\0';
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && !quote)
		{
			if (buf_index > 0)
			{
				buffer[buf_index] = '\0';
				add_token(&head, buffer);
				buf_index = 0;
			}
		}
		else if (line[i] == '"' || line[i] == '\'')
		{
			if (!quote)
				quote = line[i];
			else if (quote == line[i])
				quote = '\0';
			else
				buffer[buf_index++] = line[i];
		}
		else if (ft_strchr("|<>", line[i]) && !quote)
		{
			if (buf_index > 0)
			{
				buffer[buf_index] = '\0';
				add_token(&head, buffer);
				buf_index = 0;
			}
			buffer[0] = line[i];
			buffer[1] = '\0';
			add_token(&head, buffer);
		}
		else
			buffer[buf_index++] = line[i];
		i++;
	}
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		add_token(&head, buffer);
	}
	return (head);
}

t_token	*add_token(t_token **head, char *str)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = malloc(sizeof(t_token));
/* 	if (!new_token)
		return (NULL); */
	new_token->value = ft_strdup(str);
	new_token->type = determine_token_type(new_token->value);
	new_token->next = NULL;
	if (*head == NULL)
	{
		*head = new_token;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	return (new_token);
}

t_token_type	determine_token_type(char *str)
{
	if (ft_strcmp(str, "-") == 0)
		return (ARGUMENT);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (REDIRECT_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIRECT_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(str, "&&") == 0)
		return (AND);
	else if (ft_strcmp(str, "||") == 0)
		return (OR);
	else
		return (COMMAND);
}

void print_tokens(t_token *head)
{
    t_token *current = head;
    while (current != NULL)
    {
        // Print the value and type of each token
        printf("Token: '%s', Type: %d\n", current->value, current->type);
        current = current->next;
    }
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
    char *line;
    t_token *tokens;

    // Get input from the user
    line = readline("minishell> ");
    if (!line)
    {
        perror("readline");
        return (EXIT_FAILURE);
    }

    // Tokenize the input line
    tokens = tokenize(line);

    // Print the tokens
    print_tokens(tokens);

    // Free allocated memory for the tokens
    t_token *temp;
    while (tokens != NULL)
    {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }

    // Free the input line
    free(line);
    
    return (EXIT_SUCCESS);
}

/* cc -Wall -Wextra -Werror -lreadline tokenize.c ../lib/libft/libft.a */
