/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2024/12/20 10:16:55 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/* void	free_args(char **args)
{
	for (int i = 0; args[i]; i++)
		free(args[i]);
	free(args);
} */

char *get_name(char **env)
{
	char *user = NULL;
	int i = 0;

	if (!env)
		return (ft_strdup("minishell $ "));

	while (env[i])
	{
		if (ft_strncmp("USER=", env[i], 5) == 0)
		{
			user = ft_strjoin(PURPLEB, env[i] + 5);
			break;
		}
		i++;
	}
	if (!user)
		user = ft_strjoin(PURPLEB, "unknown");
	char *prompt = ft_strjoin(user, BLUEB"@minishell $ "X);
	free(user);
	return (prompt);
}

void	print(char **str)
{
	int i = 0;

	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	char		*name;
	t_mini		*mini;

	(void)argv;
	(void)argc;
	signal(SIGINT, ft_handle_sigint);
    signal(SIGQUIT, SIG_IGN);
	while (1)
	{
	    name = get_name(env);
	    if (!name)
	    {
	        perror("Error: No se pudo obtener el nombre del prompt\n");
	        break;
	    }
	    line = readline(name);
	    free(name);
	    if (!line)
	    {
	        printf("Error al leer la línea.\n");
	        break;
	    }
	    if (ft_strlen(line) > 0)
	    {
			mini = ft_process_input(line, env);
	        add_history(line);
	        process_command2(mini);
			free(line);
	    }
		if (mini)
			ft_free_mini(mini);
		mini = NULL;
	}
	rl_clear_history();
	return (0);
}

/* 		valgrind --leak-check=full --suppressions=readline.supp ./minishell		*/