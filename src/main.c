/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:25:53 by eandres           #+#    #+#             */
/*   Updated: 2025/01/19 17:44:30 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_name(char **env)
{
	char	*user;
	char	*prompt;
	int		i;

	i = 0;
	user = NULL;
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
	prompt = ft_strjoin(user, BLUEB"@minishell $ "X);
	free(user);
	return (prompt);
}

static	void	util_main(t_mini *mini, char *line, char **env)
{
	if (line[0] == ' ' || line[0] == '\0')
	{
		free(line);
		return ;
	}
	if (ft_strlen(line) > 0)
	{
		mini = ft_process_input(mini, line, env);
		add_history(line);
		if (!mini)
		{
			free(line);
			mini = ft_initialize_mini_node(env);
			return ;
		}
		process_command2(mini);
		free(line);
	}
	ft_clean_and_reset(mini);
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
		util_main(mini, line, env);
	}
	ft_free_mini(mini);
	rl_clear_history();
	return (0);
}
