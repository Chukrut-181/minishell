/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2024/11/05 11:50:23 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_name(char **env)
{
	char *user = NULL;
    char *pwd = NULL;

	if (!env)
		return (NULL);
	while (*env)
	{
		if (ft_strncmp("USER=", *env, 5) == 0)
			user = *env + 5;
		else if (ft_strncmp("PWD=", *env, 4) == 0)
			pwd = *env + 4;
		env++;
	}
	char *prompt = ft_strjoin(user, "@minishell ");
	char *result = ft_strjoin(prompt, pwd);
	free(prompt);
	return (result);
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	(void)env;
	char *line;
	char *name;

	while (1)
	{
		name = get_name(env);
		line = readline(name);
	}
	free(line);
	return (0);
}
