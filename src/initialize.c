/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:39:10 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/11 12:02:54 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

int	ft_locate_pipe(char **array, int *index)
{
	int	i;

	i = 1;
	while (array && array[i])
	{
		if (!ft_strcmp(array[i], "|"))
		{
			*index = *index + i;
			return (1);
		}
		else
			i++;		
	}
	return (0);
}

void	ft_get_full_command(t_mini *node, char **array)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	if (array && array[k] && *array[k] == '<')
		k += 2;
	i = 0;
	while (array && array[k] && (*array[k] != '|' && *array[k] != '>'))
	{
		k++;
		i++;
	}
	node->full_cmd = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i)
	{
		node->full_cmd[j] = ft_strdup(array[k - i]);
		j++;
		k++;
	}
	node->full_cmd[j] = NULL;
	node->full_path = node->full_cmd[0];
}

void	ft_check_redirections(t_mini *node, char **array)
{
	int	i;

	i = 0;
	if (!array || !array[i])
		return ;	
	if (array && array[i] && *array[i] == '<')
	{
		node->infile = open(array[i + 1], O_RDONLY);
		//close(node->infile);
	}
	if (array && ft_arraylen(array) - 2 >= 0
		&& *array[ft_arraylen(array) - 2] == '>')
	{
		node->outfile = open(array[ft_arraylen(array) - 1 + i],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		//close(node->outfile);
	}
}

t_mini	*ft_initialize_mini_node(char **envp)
{
	t_mini	*new_node;

	new_node = malloc(sizeof(t_mini));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_mini));
	ft_get_full_envp(new_node, envp);
	new_node->infile = STDIN_FILENO;
	new_node->outfile = STDOUT_FILENO;
	new_node->next = NULL;
	return (new_node);
}

t_mini	*ft_create_structure(char **array, char **envp)
{
	t_mini	*head;
	t_mini	*node;
	t_mini	*next_node;
	int		index;
	
	node = ft_initialize_mini_node(envp);
	head = node;
	index = 0;
	while (1)
	{
		ft_check_redirections(node, &array[index]);
		ft_get_full_command(node, &array[index]);
		if (!ft_strcmp(node->full_path, "echo") || !ft_strcmp(node->full_path, "cd")
			|| !ft_strcmp(node->full_path, "pwd")
			|| !ft_strcmp(node->full_path, "export")
			|| !ft_strcmp(node->full_path, "unset")
			|| !ft_strcmp(node->full_path, "env")
			|| !ft_strcmp(node->full_path, "exit"))
		{
			node->is_builtin = 1;
		}
		if (!ft_locate_pipe(&array[index], &index))
			break ;
		next_node = ft_initialize_mini_node(envp);
		node->next = next_node;
		node = next_node;
	}
	return (head);
}
