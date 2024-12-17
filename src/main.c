/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2024/12/17 10:28:18 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	free_args(char **args)
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
			user = ft_strjoin(PURPLEB, env[i] + 5);
			break;
		}
		i++;
	}
	if (!user)
		user = ft_strjoin(PURPLEB, "unknown");
	//pwd = ft_strjoin(pwd, BLUE" $ "X);
	char *prompt = ft_strjoin(user, BLUEB"@minishell $ "X);
	//char *result = ft_strjoin(prompt, pwd);
	free(user);
	//free(pwd);
	return (prompt);
}

/* int main(int argc, char **argv, char **env)
{
	char		*line;
	char		*name;
	t_mini		*mini;

	(void)argv;
	(void)argc;
	//mini = ft_calloc(1, sizeof(t_mini));
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
	        process_command(mini, line);
			free(line);
	    }
		//free(line);
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
} */

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
	/*
	* Set a custom handler for SIGINT (Ctrl-C).
	* When Ctrl-C is pressed, the handle_sigint function is called to
	* print a new line and redisplay the prompt, preventing the shell 
	* from terminating.
	*/

	/*
	* Ignore the SIGQUIT signal (Ctrl-\).
	* This prevents the shell from being terminated or producing a core dump
	* when Ctrl-\ is pressed, ensuring no disruptive behavior occurs.
	*/
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
			print(mini->full_cmd);
			if (mini->full_path)
				printf("%s\n", mini->full_path);
			printf("%s\n", mini->envp[0]);
			printf("%d\n", mini->is_builtin);
	        add_history(line);
	        process_command(mini);
			free(line);
	    }
		//free(line);
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
