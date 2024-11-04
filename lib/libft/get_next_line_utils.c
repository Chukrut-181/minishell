/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:58:14 by eandres           #+#    #+#             */
/*   Updated: 2024/06/18 09:48:17 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cut_buffer(char *buffer)
{
	int	i;
	int	t;

	i = 0;
	t = mod_strchr(buffer, '\n');
	while (buffer[i + t] != '\0')
	{
		buffer[i] = buffer[i + t + 1];
		i++;
	}
	while (i <= BUFFER_SIZE)
		buffer[i++] = '\0';
}

int	mod_strchr(char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && (char)c != str[i])
		i++;
	if ((char)c == str[i])
		return (i);
	return (-1);
}

char	*mod_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*result;

	if (!s2)
		return (s1);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	c = 0;
	while (s2[c - 1] != '\n' && s2[c] != '\0')
	{
		result[i + c] = s2[c];
		c++;
	}
	result[i + c] = '\0';
	free(s1);
	return (result);
}

void	mod_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = 0;
}
