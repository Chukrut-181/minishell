/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2024/11/20 14:03:34 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void free_args(char **args)
{
	for (int i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

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
			user = ft_strjoin(GREEN, env[i] + 5);
			break;
		}
		i++;
	}
	if (!user)
		user = ft_strjoin(GREEN, "unknown");
	//pwd = ft_strjoin(pwd, BLUE" $ "X);
	char *prompt = ft_strjoin(user, YELLOW"@minishell $ "X);
	//char *result = ft_strjoin(prompt, pwd);
	free(user);
	//free(pwd);
	return (prompt);
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	char		*name;
	t_mini		*mini;
	//t_prompt	*prompt;

	(void)argv;
	(void)argc;
	mini = initialize_mini(env);
	while (1)
	{
	    name = get_name(mini->env_copy);
	    if (!name)
	    {
	        perror("Error: No se pudo obtener el nombre del prompt\n");
	        break;
	    }
	    line = readline(name);
	    free(name);
	    if (!line)
	    {
	        printf("\nhola\n");
	        break;
	    }
	    if (ft_strlen(line) > 0)
	    {
	        add_history(line);
	        process_command(mini, line);
	    }
	    free(line);
	}
	if (mini->full_path)
		free(mini->full_path);
	if (mini->env_copy)
	{
		for (int i = 0; mini->env_copy[i]; i++)
			free(mini->env_copy[i]);
		free(mini->env_copy);
	}
	free(mini);
	rl_clear_history();
	return (0);
}
