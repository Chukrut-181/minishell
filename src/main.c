/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2024/11/07 13:02:00 by eandres          ###   ########.fr       */
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
    char cwd[MAX_PATH];
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
    mini->full_cmd = NULL;
    mini->full_path = getcwd(NULL, 0);
    mini->is_builtins = 0;
    mini->infile = STDIN_FILENO;
    mini->outfile = STDOUT_FILENO;
    while (1)
    {
        name = get_name(env);
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
                for (int i = 0; args[i]; i++)
                    free(args[i]);
                free(args);
                mini->full_cmd = NULL;
            }
        }
        else if (ft_strcmp(line, "pwd") == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
            else
                perror("getcwd() error");
        }
        if (ft_strlen(line) > 0)
            add_history(line);
        
        free(line);
    }
    if (mini->full_path)
        free(mini->full_path);
    free(mini);
    rl_clear_history();
    return (0);
}

/* int main()
{
	t_mini mini;
	char *commands[][3] = {
		{"cd", NULL, NULL},
		{"cd", "-", NULL},
		{"cd", "..", NULL},
		{"cd", "/tmp", NULL}
	};
	int num_commands = sizeof(commands) / sizeof(commands[0]);

	// Inicializar la estructura
	mini.is_builtins = 1;
	mini.infile = STDIN_FILENO;
	mini.outfile = STDOUT_FILENO;

	// Obtener el directorio actual
	mini.full_path = getcwd(NULL, 0);
	if (mini.full_path == NULL)
	{
		perror("Error obteniendo el directorio actual");
		return 1;
	}

	printf("Directorio inicial: %s\n", mini.full_path);

	// Probar diferentes comandos cd
	for (int i = 0; i < num_commands; i++)
	{
		mini.full_cmd = commands;
		
		printf("\nEjecutando: ");
		for (int j = 0; mini.full_cmd[j] != NULL; j++)
		{
			printf("%s ", mini.full_cmd[j]);
		}
		printf("\n");

		management_cd(&mini);
		
		printf("Nuevo directorio: %s\n", mini.full_path);
	}
} */
