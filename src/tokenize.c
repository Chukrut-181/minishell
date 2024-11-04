/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:23:07 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/04 14:03:33 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *line)
{
	t_token *head;
	char	**array;
	int		i;

	array = ft_split(line, ' ');
	i = 0;
	while (array[i])
	{
		add_token(&head, array[i]);
		i++;
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
	new_token->type = determine_token_type(new_token);
	new_token->next = NULL;
	if (head == NULL)
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

t_token_type	determine_token_type(t_token *new_token)
{
	if (new_token->value == '|')
		return (PIPE);
	if (new_token->value[0] == '-')
		return (ARGUMENT);
	if (new_token->value == '<' || new_token->value == '>')
		return (REDIRECT_IN);
	if (new_token->value == '>')
		return (REDIRECT_OUT);
}
