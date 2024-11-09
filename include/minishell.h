/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:19:09 by eandres           #+#    #+#             */
/*   Updated: 2024/11/09 07:56:36 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// habria que incluir la libft y el pipex
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <signal.h>
#include "../lib/libft/libft.h"

#define HOME "/home/eandres"
#define MAX_PATH 1024

#define RED			"\033[0;31m"
# define GREEN		"\033[0;32m"
# define GREENB		"\033[32;1m"
# define YELLOW		"\033[0;33m"
# define BLUE 		"\033[0;34m"
# define BLUEB 		"\033[34;1m"
# define PURPLE		"\033[0;35m"
# define PURPLEB	"\033[35;1m"
# define CYAN		"\033[0;36m"
# define BOLD		"\033[0;1m"
# define X			"\033[0;0m"

typedef struct s_prompt
{
	t_list	*cmds;
	pid_t	pid;
}			t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	char	**envp;
	char	**env_copy;
	int		is_builtins;
	int		infile;
	int		outfile;
}			t_mini;

void management_unset(t_mini *mini);
int count_val(const char *val);
char **create_env_copy(char **env);
void update_env_copy(t_mini *mini);
char *my_getenvp(const char *name, char **env_copy);
int my_setenv(const char *name, const char *value, int overwrite, t_mini *mini);
void management_pwd(void);
void management_env(t_mini *mini);
void management_cd(t_mini *mini);
void update_pwd(t_mini *mini);

#endif