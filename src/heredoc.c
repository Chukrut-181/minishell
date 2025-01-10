/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:01:20 by igchurru          #+#    #+#             */
/*   Updated: 2025/01/10 13:48:29 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* If here_doc was found, this function will create a .tmp file to store the
input from the terminal until the limiter is found. */
void	ft_create_tmp(t_mini *node)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(node->limit, "\n");
	node->infile = open(".temp", O_CREAT | O_TRUNC | O_RDWR, 0777);
	while (true)
	{
		line = get_one_line(0);
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0)
		{
			free(limiter);
			break ;
		}
		ft_putstr_fd(line, node->infile);
		free(line);
	}
	free(line);
	//close(node->infile);
}

/* getline will read from the terminal one char at a time and create a string
to be returned to the create_tmp function. Pay extra attention to aux: it is only
used to avoid memory leaks. */
char	*get_one_line(int fd)
{
	char	c;
	char	*str;
	char	*temp;
	char	*aux;

	str = malloc(1 * sizeof(char));
	str[0] = 0;
	while (read(fd, &c, 1) > 0)
	{
		aux = str;
		temp = malloc(2 * sizeof(char));
		temp[0] = c;
		temp[1] = 0;
		str = ft_strjoin(aux, temp);
		free(temp);
		free(aux);
		if (c == '\n')
			break ;
	}
	return (str);
}
