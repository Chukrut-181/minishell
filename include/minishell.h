/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:19:09 by eandres           #+#    #+#             */
/*   Updated: 2024/11/05 10:28:58 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// habria que incluir la libft y el pipex
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../lib/libft/libft.h"

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	AND,
	OR,
	SEPARATOR,
	QUOTED_STRING,
	ENV_VARIABLE,	
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

//	TOKENIZE.C
t_token			*tokenize(char *line);
t_token			*add_token(t_token **head, char *str);
t_token_type	determine_token_type(char *str);

//	MAIN.C
int				main(int argc, char **argv, char **env);
char			*get_name(char **env);

#endif