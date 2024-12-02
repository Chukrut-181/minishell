/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:19:09 by eandres           #+#    #+#             */
/*   Updated: 2024/11/28 12:24:44 by igchurru         ###   ########.fr       */
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
#include <stdbool.h>

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

typedef struct s_mini
{
	char			*command;
	char			**full_cmd;
	char			*full_path;
	char			**envp;
	char			**env_copy; 
	int				is_builtin;
	int				infile;
	int				outfile;
	pid_t			pid;
	struct s_mini	*next;
}					t_mini;

// builtins
int management_builtins(t_mini *mini);
void management_pwd(void);
void management_cd(t_mini *mini);
void management_env(t_mini *mini);
void management_unset(t_mini *mini);
void management_echo(t_mini *mini);
int management_export(t_mini *mini);
void management_exit(t_mini *mini);

//builtins utils
void update_pwd(t_mini *mini);
char **create_env_copy(char **env);
char *my_getenvp(const char *name, char **env_copy);
int set_env_var(t_mini *mini, const char *name, const char *value);
int	is_valid(char *str);

//execute command
char	*get_path(t_mini *mini);
int		process_command(t_mini *mini, char *line);
void	execute_external_command(t_mini *mini);

//other
void free_args(char **args);

//parse
t_mini	*initialize_mini(char **env);
char	*ft_strtrim_quotes(char const *s1, int squote, int dquote);
int		count_quotes(char const *s1);

#endif