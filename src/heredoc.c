/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:01:20 by igchurru          #+#    #+#             */
/*   Updated: 2025/01/17 15:18:52 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_create_tmp(t_mini *node)
{
	char	*line;
	char	*limiter;
	int		pipefd[2];

	limiter = ft_strjoin(node->limit, "\n");
	if (pipe(pipefd) < 0)
		printf("Error creating here_doc\n");
	node->infile = pipefd[0];
	while (true)
	{
		line = get_one_line(0);
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0)
		{
			free(limiter);
			break ;
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	free(line);
	close(pipefd[1]);
}

char	*get_one_line(int fd)
{
	char	c;
	char	*str;
	char	*temp;
	char	*aux;

	str = malloc(1 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	while (read(fd, &c, 1) > 0)
	{
		aux = str;
		temp = malloc(2 * sizeof(char));
		if (!temp)
			return (NULL);
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
