/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2024/11/05 17:38:28 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char *get_name(char **env)
{
	char *user = NULL;
    char *pwd = NULL;
	int i = 0;

	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp("USER=", env[i], 5) == 0)
			user = ft_strjoin(YELLOW, env[i] + 5);
		else if (ft_strncmp("PWD=", env[i], 4) == 0)
			pwd = ft_strjoin(BLUE, env[i] + 4);
		i++;
	}
	pwd = ft_strjoin(pwd, BLUE" $ "X);
	char *prompt = ft_strjoin(user, YELLOW"@minishell "X);
	char *result = ft_strjoin(prompt, pwd);
	free(result);
	return (prompt);
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
		add_history(line);
		rl_on_new_line();
	}
	printf("el historial es: %d\n", history_length);
	rl_clear_history();
	printf("el historial es: %d\n", history_length);
	free(line);
	return (0);
}
