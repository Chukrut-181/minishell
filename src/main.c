/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2024/11/09 09:33:09 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void free_args(char **args)
{
	for (int i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

char *get_name(char **env)
{
	char *user = NULL;
	//char *pwd = NULL;
	int i = 0;

	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp("USER=", env[i], 5) == 0)
			user = ft_strjoin(GREEN, env[i] + 5);
		//else if (ft_strncmp("PWD=", env[i], 4) == 0)
			//pwd = ft_strjoin(BLUE, env[i] + 4);
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
	(void)argv;
	(void)argc;
	char *line;
	char *name;
	t_mini *mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
	{
		fprintf(stderr, "Error: No se pudo asignar memoria para mini\n");
		return (1);
	}
	mini->envp = env;
	mini->env_copy = create_env_copy(env);
	if (!mini->env_copy)
	{
		fprintf(stderr, "Error: No se pudo crear una copia del entorno\n");
		free(mini);
		return (1);
	}
	mini->full_cmd = NULL;
	mini->full_path = getcwd(NULL, 0);
	mini->is_builtins = 0;
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	while (1)
	{
		name = get_name(mini->env_copy);
		if (!name)
		{
			fprintf(stderr, "Error: No se pudo obtener el nombre del prompt\n");
			break;
		}
		line = readline(name);
		free(name);
		if (!line)
		{
			printf("\nSaliendo de minishell\n");
			break;
		}
		if (ft_strncmp(line, "cd", 2) == 0)
		{
			char **args = ft_split(line, ' ');
			if (args)
			{
				mini->full_cmd = args;
				management_cd(mini);
				free_args(args);
				mini->full_cmd = NULL;
			}
		}
		else if (ft_strcmp(line, "pwd") == 0)
		{
			management_pwd();
		}
		else if (ft_strcmp(line, "env") == 0)
		{
			management_env(mini);
		}
		else if (ft_strncmp(line, "unset", 5) == 0)
		{
			char **args = ft_split(line, ' ');
			if (args)
			{
				mini->full_cmd = args;
				management_unset(mini);
				free_args(args);
				mini->full_cmd = NULL;
			}
		}
		if (ft_strlen(line) > 0)
			add_history(line);
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
