/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:39:10 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/03 12:02:45 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

void	ft_get_full_command(t_mini *node, char **array)
{
	int	i;
	int	j;

	i = 0;
	while(array && array[i] && *array[i] != '|')
	{
		i++;
	}
	node->full_cmd = malloc(sizeof(char *) * i);
	j = 0;
	while(j < i)
	{
		node->full_cmd[j] = array[j];
		j++;
	}
	node->full_cmd[j] = NULL;
}
void	ft_check_redirections(t_mini *node, char **array)
{
	if (array && *array[0] == '<')
	{
		node->infile = open(array[1], O_RDONLY);
		//close(node->infile);
	}
	if (array && *array[ft_arraylen(array) - 2] == '>')
	{
		node->outfile = open(array[ft_arraylen(array) - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
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
	int		i;

	node = ft_initialize_mini_node(envp);
	head = node;
	ft_check_redirections(node, array);
	ft_get_full_command(node, array);
	i = 0;
	printf("In  fd: %d\n", node->infile);
	printf("Out fd: %d\n", node->outfile);
/* 	while (node && node->full_cmd && node->full_cmd[i])
	{
		printf("%s\n", node->full_cmd[i]);
		i++;
	} */
	
	return (head);
}
