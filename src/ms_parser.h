/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:40:11 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/28 14:56:01 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSER_H
# define MS_PARSER_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>

typedef struct s_mini
{
	char			*command;
	char			**full_cmd;
	char			*full_path;
	char			**env_vars;
	char			**env_copy;
	int				is_builtin;
	int				infile;
	int				outfile;
	pid_t			pid;
	struct s_mini	*next;
}					t_mini;

char	**ft_process_input(char *line, char **envp);
char	**ft_split_prompt(char const *s, char c);
char	*ft_expand_path(char *word, int index);
char	*ft_expand_variable(char *word, int index);
char	*ft_strtrim_quotes(const char *s1, int squote, int dquote);
int		ft_count_quotes(char const *s1);
char	ft_get_quote_context(const char *s, int index);
int		ft_get_var_name_len(const char *var_name);
char	**ft_expand(char **temp);
char	**ft_extract_operators(char **s, const char *operators);
int		ft_arraylen(char **array);
char	**ft_create_temp_array(char **array, int i, int j);
char	**ft_concatenate_array(char **array, char **temp_array, int index);
char	**ft_final_trim(char **array);
t_mini	*ft_initialize_mini_node(char **envp);
void	ft_get_full_envp(t_mini *node, char **envp);

void	ft_free_array(char **array);

#endif