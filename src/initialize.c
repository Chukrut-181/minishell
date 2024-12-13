/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:39:10 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/13 11:49:06 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_locate_pipe(char **array, int *index)
{
	int	i;

	i = 1;
	while (array && array[i])
	{
		if (!ft_strcmp(array[i], "|"))
		{
			*index = *index + i + 1;
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
}

void	ft_check_redirections(t_mini *node, char **array)
{
	int	i;
	int	len;

	i = 0;
	if (!array || !array[i])
		return ;
	if (array && array[i] && *array[i] == '<')
		node->infile = open(array[i + 1], O_RDONLY);
	while (array[i])
	{
		if (*array[i] == '|')
			return ;
		else
			i++;
	}
	len = ft_arraylen(array);
	if (array && len - 2 >= 0 && *array[len - 2] == '>')
	{
		node->outfile = open(array[len - 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
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
		ft_check_if_builtin(node);
		ft_get_path(node);
		if (!ft_locate_pipe(&array[index], &index))
			break ;
		next_node = ft_initialize_mini_node(envp);
		node->next = next_node;
		node = next_node;
	}
	return (head);
}
