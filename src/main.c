/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2025/01/15 14:09:08 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_name(char **env)
{
	char	*user = NULL;
	int		i = 0;

	if (!env)
		return (ft_strdup("minishell $ "));
	while (env[i])
	{
		if (ft_strncmp("USER=", env[i], 5) == 0)
		{
			user = ft_strjoin(PURPLEB, env[i] + 5);
			break ;
		}
		i++;
	}
	if (!user)
		user = ft_strjoin(PURPLEB, "unknown");
	char *prompt = ft_strjoin(user, BLUEB"@minishell $ "X);
	free(user);
	return (prompt);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*name;
	t_mini	*mini;

	(void)argv;
	(void)argc;
	setup_signals();
	mini = ft_initialize_mini_node(env);
	while (1)
	{
		name = get_name(mini->env_copy);
		if (!name)
		{
			perror("Error: No se pudo obtener el nombre del prompt\n");
			break ;
		}
		line = readline(name);
		free(name);
		if (!line)
			break ;
		if (line[0] == ' ' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (ft_strlen(line) > 0)
		{
			mini = ft_process_input(mini, line, env);
			add_history(line);
			if (!mini)
			{
				free(line);
				continue ;
			}
			process_command2(mini);
			free(line);
		}
		ft_clean_and_reset(mini);
	}
	ft_free_mini(mini);
	rl_clear_history();
	return (0);
}

/* 		valgrind --leak-check=full --suppressions=readline.supp ./minishell		*/
