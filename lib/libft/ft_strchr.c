/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:02:15 by eandres           #+#    #+#             */
/*   Updated: 2024/04/23 17:57:00 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (*str != '\0' && (char)c != str[i])
		i++;
	if ((char)c == str[i])
		return ((char *)&str[i]);
	return (0);
}

/* int main()
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 30);
	if (buffer == NULL)
		return (0);
	if (!ft_strchr(buffer, '\n'))
		write(1, "si", 2);
	else
		write(1, "no", 2);
	return (0);
} */
